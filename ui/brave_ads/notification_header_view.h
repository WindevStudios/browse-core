/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_NOTIFICATION_HEADER_VIEW_H_
#define BRAVE_UI_BRAVE_ADS_NOTIFICATION_HEADER_VIEW_H_

#include "base/strings/string16.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/metadata/metadata_header_macros.h"

namespace views {
class Label;
class View;
}  // namespace views

namespace brave_ads {

class NotificationHeaderView : public views::Button {
 public:
  METADATA_HEADER(NotificationHeaderView);

  explicit NotificationHeaderView(PressedCallback callback);
  ~NotificationHeaderView() override;

  void SetTitle(const base::string16& name);
  void SetTitleElideBehavior(gfx::ElideBehavior elide_behavior);

 private:
  void BuildView();

  views::Label* title_label_ = nullptr;
  views::Label* CreateTitleLabel();

  views::View* CreateSpacerView(const int spacing);

  NotificationHeaderView(const NotificationHeaderView&) = delete;
  NotificationHeaderView& operator=(const NotificationHeaderView&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_NOTIFICATION_HEADER_VIEW_H_
