/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_PADDED_IMAGE_BUTTON_H_
#define BRAVE_UI_BRAVE_ADS_PADDED_IMAGE_BUTTON_H_

#include <memory>

#include "ui/views/controls/button/image_button.h"
#include "ui/views/metadata/metadata_header_macros.h"

namespace views {
class InkDrop;
}  // namespace views

namespace brave_ads {

class PaddedImageButton : public views::ImageButton {
 public:
  METADATA_HEADER(PaddedImageButton);

  explicit PaddedImageButton(PressedCallback callback);
  ~PaddedImageButton() override = default;

  std::unique_ptr<views::InkDrop> CreateInkDrop() override;
  void OnThemeChanged() override;

 private:
  PaddedImageButton(const PaddedImageButton&) = delete;
  PaddedImageButton& operator=(const PaddedImageButton&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_PADDED_IMAGE_BUTTON_H_
