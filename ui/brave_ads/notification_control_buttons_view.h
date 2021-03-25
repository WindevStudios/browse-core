/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_NOTIFICATION_CONTROL_BUTTONS_VIEW_H_
#define BRAVE_UI_BRAVE_ADS_NOTIFICATION_CONTROL_BUTTONS_VIEW_H_

#include "ui/views/metadata/metadata_header_macros.h"
#include "ui/views/view.h"

namespace views {
class Button;
}

namespace brave_ads {

class NotificationView;
class PaddedImageButton;
class PaddedImageView;

class NotificationControlButtonsView : public views::View {
 public:
  METADATA_HEADER(NotificationControlButtonsView);

  explicit NotificationControlButtonsView(NotificationView* message_view);
  ~NotificationControlButtonsView() override;

  // Change the visibility of the info button. Set |should_show| to true to
  // show, false to hide
  void ShowInfoButton(const bool should_show);

  // Change the visibility of the close button. Set |should_show| to true to
  // show, false to hide
  void ShowCloseButton(const bool should_show);

  // Change the visibility of all buttons. Set |should_show| to true to show,
  // false to hide
  void ShowButtons(const bool should_show);

 private:
  NotificationView* notification_view_ = nullptr;

  PaddedImageView* info_button_ = nullptr;
  PaddedImageButton* close_button_ = nullptr;

  NotificationControlButtonsView(const NotificationControlButtonsView&) =
      delete;
  NotificationControlButtonsView& operator=(
      const NotificationControlButtonsView&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_NOTIFICATION_CONTROL_BUTTONS_VIEW_H_
