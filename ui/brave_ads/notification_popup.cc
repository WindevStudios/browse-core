/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/notification_popup.h"

#include <map>
#include <memory>
#include <utility>

#include "base/bind.h"
#include "brave/ui/brave_ads/notification_view.h"
#include "brave/ui/brave_ads/notification_view_factory.h"
#include "brave/ui/brave_ads/public/cpp/constants.h"
#include "build/build_config.h"
#include "ui/display/display.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/metadata/metadata_impl_macros.h"
#include "ui/views/widget/widget.h"

#if defined(OS_WIN)
#include "ui/views/widget/desktop_aura/desktop_native_widget_aura.h"
#endif

namespace brave_ads {

namespace {

// TODO(https://github.com/brave/brave-browser/issues/14957): Decouple
// NotificationPopup management to NotificationPopupCollection
std::map<std::string, NotificationPopup*> g_notification_popups;

const int kWidgetPadding = 10;

}  // namespace

NotificationPopup::NotificationPopup(const Notification& notification)
    : notification_(notification) {
  SetLayoutManager(std::make_unique<views::FillLayout>());

  CreateWidget();
}

NotificationPopup::~NotificationPopup() = default;

// static
void NotificationPopup::Show(const Notification& notification) {
  const std::string& notification_id = notification.id();

  DCHECK(!g_notification_popups[notification_id]);
  g_notification_popups[notification_id] = new NotificationPopup(notification);
}

// static
void NotificationPopup::Close(const std::string& notification_id,
                              const bool by_user) {
  DCHECK(!notification_id.empty());

  NotificationPopup* notification_popup =
      g_notification_popups[notification_id];
  DCHECK(notification_popup);

  NotificationDelegate* notification_delegate =
      notification_popup->notification_.delegate();
  if (notification_delegate) {
    notification_delegate->OnClose(by_user);
  }

  NotificationView* notification_view =
      notification_popup->GetNotificationView();
  DCHECK(notification_view);

  // Destroy the widget when done. The observer deletes itself on completion
  notification_view->FadeOut(base::BindOnce(
      [](const std::string& notification_id) {
        DCHECK(!notification_id.empty());

        NotificationPopup* notification_popup =
            g_notification_popups[notification_id];
        DCHECK(notification_popup);

        g_notification_popups.erase(notification_id);

        notification_popup->CloseWidgetViewForId(notification_id);
      },
      notification_id));
}

// static
void NotificationPopup::OnClick(const std::string& notification_id) {
  DCHECK(!notification_id.empty());

  NotificationPopup* notification_popup =
      g_notification_popups[notification_id];
  DCHECK(notification_popup);

  NotificationDelegate* delegate = notification_popup->notification_.delegate();
  if (delegate) {
    delegate->OnClick();
  }

  Close(notification_id, /* by_user */ true);
}

///////////////////////////////////////////////////////////////////////////////

#if !defined(OS_WIN) && !defined(OS_MAC)
gfx::Rect NotificationPopup::GetVisibleFrameForPrimaryDisplay() const {
  return gfx::Rect(display::Screen::GetScreen()->GetPrimaryDisplay().size());
}
#endif

gfx::Rect NotificationPopup::GetBounds() const {
  const gfx::Rect visible_frame = GetVisibleFrameForPrimaryDisplay();

  const int x = visible_frame.right() - (kNotificationWidth + kWidgetPadding);

#if defined(OS_WIN)
  const int y = visible_frame.bottom() - (kNotificationHeight + kWidgetPadding);
#else
  const int y = visible_frame.y() + kWidgetPadding;
#endif

  return gfx::Rect(x, y, kNotificationWidth, kNotificationHeight);
}

void NotificationPopup::CreateWidget() {
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_POPUP);
  params.z_order = ui::ZOrderLevel::kFloatingWindow;
  params.type = views::Widget::InitParams::TYPE_WINDOW_FRAMELESS;
  params.delegate = this;
  params.name = "BraveAdsNotificationPopup";
  params.opacity = views::Widget::InitParams::WindowOpacity::kTranslucent;
  params.bounds = GetBounds();

#if defined(OS_WIN)
  // We want to ensure that this toast always goes to the native desktop,
  // not the Ash desktop (since there is already another toast contents view
  // there
  if (!params.parent) {
    DCHECK(!params.native_widget);
    params.native_widget = new views::DesktopNativeWidgetAura(widget_view_);
  }
#endif

  DCHECK(!widget_view_);
  widget_view_ = new views::Widget();
  widget_view_->set_focus_on_creation(false);
  observation_.Observe(widget_view_);

  widget_view_->Init(std::move(params));

  notification_view_ = NotificationViewFactory::Create(notification_);
  widget_view_->SetContentsView(notification_view_);

  widget_view_->ShowInactive();
}

NotificationView* NotificationPopup::GetNotificationView() const {
  return notification_view_;
}

void NotificationPopup::CloseWidgetViewForId(
    const std::string& notification_id) const {
  DCHECK(!notification_id.empty());
  DCHECK(widget_view_);

  widget_view_->CloseNow();
}

void NotificationPopup::OnWidgetDestroyed(views::Widget* widget) {
  DCHECK(observation_.IsObservingSource(widget));
  observation_.Reset();
}

BEGIN_METADATA(NotificationPopup, views::WidgetDelegateView)
END_METADATA

}  // namespace brave_ads
