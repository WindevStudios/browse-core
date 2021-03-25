/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_NOTIFICATION_VIEW_H_
#define BRAVE_UI_BRAVE_ADS_NOTIFICATION_VIEW_H_

#include <string>

#include "base/callback_forward.h"
#include "ui/views/animation/ink_drop_host_view.h"
#include "ui/views/metadata/metadata_header_macros.h"

namespace gfx {
class Canvas;
}  // namespace gfx

namespace brave_ads {

class Notification;

class NotificationView : public views::InkDropHostView {
 public:
  METADATA_HEADER(NotificationView);

  explicit NotificationView(const Notification& notification);
  ~NotificationView() override;

  // Updates this view with the new data contained in the notification
  virtual void UpdateForNotification(const Notification& notification);

  // Update corner radii of the notification. Subclasses should override this to
  // implement rounded corners if they do not use NotificationView's default
  // background
  virtual void UpdateCornerRadius();

  std::string GetNotificationId() const { return notification_id_; }

  void OnCloseButtonPressed();

  void FadeOut(base::OnceClosure closure);

  // views::InkDropHostView implementation
  void OnPaint(gfx::Canvas* canvas) override;
  void OnThemeChanged() override;

 private:
  std::string notification_id_;

  bool is_closing_ = false;

  void FadeIn();

  NotificationView(const NotificationView&) = delete;
  NotificationView& operator=(const NotificationView&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_NOTIFICATION_VIEW_H_
