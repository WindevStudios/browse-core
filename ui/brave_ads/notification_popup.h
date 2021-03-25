/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_NOTIFICATION_POPUP_H_
#define BRAVE_UI_BRAVE_ADS_NOTIFICATION_POPUP_H_

#include <string>

#include "base/scoped_observation.h"
#include "brave/ui/brave_ads/public/cpp/notification.h"
#include "ui/views/metadata/metadata_header_macros.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/widget/widget_observer.h"

namespace views {
class Widget;
}  // namespace views

namespace brave_ads {

class NotificationView;

// The widget delegate of a notification popup. The view is owned by the widget
class NotificationPopup : public views::WidgetDelegateView,
                          public views::WidgetObserver {
 public:
  METADATA_HEADER(NotificationPopup);

  explicit NotificationPopup(const Notification& notification);
  ~NotificationPopup() override;

  // Show the notification widget for the given |notification|
  static void Show(const Notification& notification);

  // Close the notification widget for the given |notification_id|. |by_user|
  // is true if the notification widget was closed by the user, otherwise false
  static void Close(const std::string& notification_id, const bool by_user);

  // User clicked the notification widget for the given |notification_id|
  static void OnClick(const std::string& notification_id);

 private:
  Notification notification_;

  views::Widget* widget_view_ = nullptr;

  NotificationView* notification_view_ = nullptr;  // NOT OWNED

  gfx::Rect GetVisibleFrameForPrimaryDisplay() const;

  gfx::Rect GetBounds() const;

  void CreateWidget();

  NotificationView* GetNotificationView() const;

  void CloseWidgetViewForId(const std::string& notification_id) const;

  base::ScopedObservation<views::Widget, views::WidgetObserver> observation_{
      this};

  // views::WidgetObserver implementation
  void OnWidgetDestroyed(views::Widget* widget) override;

  NotificationPopup(const NotificationPopup&) = delete;
  NotificationPopup& operator=(const NotificationPopup&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_NOTIFICATION_POPUP_H_
