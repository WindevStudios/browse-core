/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/ad_notification_view.h"

#include <string>

#include "base/bind.h"
#include "base/strings/string16.h"
#include "brave/ui/brave_ads/notification_control_buttons_view.h"
#include "brave/ui/brave_ads/notification_header_view.h"
#include "brave/ui/brave_ads/notification_popup.h"
#include "brave/ui/brave_ads/public/cpp/constants.h"
#include "brave/ui/brave_ads/public/cpp/notification.h"
#include "ui/gfx/color_palette.h"
#include "ui/gfx/font.h"
#include "ui/gfx/font_list.h"
#include "ui/gfx/geometry/insets.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

namespace brave_ads {

namespace {

constexpr gfx::Insets kContainerViewInsideBorderInsets(0, 12, 10, 6);

const int kBodyFontSize = 13;
const int kBodyLineHeight = 17;
constexpr SkColor kBodyColor = SkColorSetRGB(0x75, 0x75, 0x75);
constexpr gfx::Insets kBodyViewBorderInsets(0);

gfx::FontList GetFontList(const int font_size) {
  gfx::Font default_font;
  const int font_size_delta = font_size - default_font.GetFontSize();
  const gfx::Font font = default_font.Derive(font_size_delta, gfx::Font::NORMAL,
                                             gfx::Font::Weight::NORMAL);
  return gfx::FontList(font);
}

class AdNotificationViewEventHandler : public ui::EventHandler {
 public:
  explicit AdNotificationViewEventHandler(AdNotificationView* owner)
      : owner_(owner) {}
  ~AdNotificationViewEventHandler() override = default;

 private:
  // ui::EventHandler implementation
  void OnEvent(ui::Event* event) override {
    if (event->type() == ui::ET_MOUSE_PRESSED ||
        event->type() == ui::ET_GESTURE_TAP) {
      owner_->Activate();
    }
  }

  AdNotificationView* const owner_;

  AdNotificationViewEventHandler(const AdNotificationViewEventHandler&) =
      delete;
  AdNotificationViewEventHandler& operator=(
      const AdNotificationViewEventHandler&) = delete;
};

}  // namespace

AdNotificationView::AdNotificationView(const Notification& notification)
    : NotificationView(notification) {
  UpdateForNotification(notification);

  event_handler_ = std::make_unique<AdNotificationViewEventHandler>(this);
  AddPreTargetHandler(event_handler_.get());
}

AdNotificationView::~AdNotificationView() {
  RemovePreTargetHandler(event_handler_.get());
}

void AdNotificationView::Activate() {
  GetWidget()->widget_delegate()->SetCanActivate(true);
  GetWidget()->Activate();
}

void AdNotificationView::UpdateForNotification(
    const Notification& notification) {
  NotificationView::UpdateForNotification(notification);

  CreateView(notification);

  Layout();
  SchedulePaint();
}

void AdNotificationView::Layout() {
  NotificationView::Layout();
}

bool AdNotificationView::OnMousePressed(const ui::MouseEvent& event) {
  last_mouse_pressed_event_timestamp_ = base::TimeTicks(event.time_stamp());
  return true;
}

bool AdNotificationView::OnMouseDragged(const ui::MouseEvent& event) {
  return true;
}

void AdNotificationView::OnMouseReleased(const ui::MouseEvent& event) {
  if (!event.IsOnlyLeftMouseButton()) {
    return;
  }

  const std::string notification_id = GetNotificationId();
  NotificationPopup::OnClick(notification_id);

  NotificationView::OnMouseReleased(event);
}

void AdNotificationView::OnMouseEvent(ui::MouseEvent* event) {
  View::OnMouseEvent(event);
}

void AdNotificationView::OnThemeChanged() {
  NotificationView::OnThemeChanged();
}

//////////////////////////////////////////////////////////////////////////////

void AdNotificationView::CreateView(const Notification& notification) {
  SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical, gfx::Insets()));

  // Header
  NotificationHeaderView* header_view = CreateHeaderView(notification);
  NotificationControlButtonsView* control_buttons_view =
      CreateControlButtonsView(notification);
  header_view->AddChildView(control_buttons_view);
  AddChildView(header_view);

  // Body
  container_view_ = new views::View();
  views::BoxLayout* layout_manager =
      container_view_->SetLayoutManager(std::make_unique<views::BoxLayout>(
          views::BoxLayout::Orientation::kHorizontal,
          kContainerViewInsideBorderInsets));
  layout_manager->set_cross_axis_alignment(
      views::BoxLayout::CrossAxisAlignment::kStart);
  AddChildView(container_view_);

  views::View* body_view = CreateBodyView(notification);
  container_view_->AddChildView(body_view);

  layout_manager->SetFlexForView(body_view, 1);
}

NotificationControlButtonsView* AdNotificationView::CreateControlButtonsView(
    const Notification& notification) {
  NotificationControlButtonsView* view =
      new NotificationControlButtonsView(this);

  view->ShowInfoButton(true);
  view->ShowCloseButton(true);
  view->ShowButtons(true);

  return view;
}

NotificationHeaderView* AdNotificationView::CreateHeaderView(
    const Notification& notification) {
  NotificationHeaderView* view = new NotificationHeaderView(base::BindRepeating(
      &AdNotificationView::HeaderViewPressed, base::Unretained(this)));

  view->SetTitle(notification.title());
  view->SetTitleElideBehavior(gfx::ELIDE_TAIL);

  return view;
}

void AdNotificationView::HeaderViewPressed() {
  const std::string notification_id = GetNotificationId();
  NotificationPopup::OnClick(notification_id);
}

views::View* AdNotificationView::CreateBodyView(
    const Notification& notification) {
  views::View* view = new views::View();

  view->SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical, gfx::Insets()));

  view->SetBorder(views::CreateEmptyBorder(kBodyViewBorderInsets));

  views::Label* label = CreateBodyLabel(notification);
  view->AddChildView(label);

  return view;
}

views::Label* AdNotificationView::CreateBodyLabel(
    const Notification& notification) {
  const base::string16 body = notification.body();

  views::Label* label = new views::Label(body);

  const gfx::FontList& font_list = GetFontList(kBodyFontSize);
  label->SetFontList(font_list);

  label->SetHorizontalAlignment(gfx::ALIGN_TO_HEAD);

  label->SetEnabledColor(kBodyColor);
  label->SetBackgroundColor(SK_ColorTRANSPARENT);

  label->SetLineHeight(kBodyLineHeight);
  label->SetMaxLines(2);
  label->SetMultiLine(true);
  label->SetAllowCharacterBreak(true);

  const int width = kNotificationWidth - GetInsets().width();
  label->SizeToFit(width);

  label->SetVisible(true);

  return label;
}

}  // namespace brave_ads
