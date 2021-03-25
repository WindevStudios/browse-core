/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/padded_image_button.h"

#include <utility>

#include "ui/gfx/geometry/insets.h"
#include "ui/views/animation/ink_drop.h"
#include "ui/views/animation/ink_drop_impl.h"
#include "ui/views/border.h"
#include "ui/views/metadata/metadata_impl_macros.h"

namespace brave_ads {

namespace {
const int kBorderInset = 6;
}  // namespace

PaddedImageButton::PaddedImageButton(PressedCallback callback)
    : views::ImageButton(callback) {
  SetBorder(views::CreateEmptyBorder(gfx::Insets(kBorderInset)));
  SetAnimateOnStateChange(false);

  SetInkDropMode(InkDropMode::ON);
  SetInkDropVisibleOpacity(0.12f);
  SetHasInkDropActionOnClick(true);
}

std::unique_ptr<views::InkDrop> PaddedImageButton::CreateInkDrop() {
  std::unique_ptr<views::InkDropImpl> ink_drop = CreateDefaultInkDropImpl();
  ink_drop->SetShowHighlightOnHover(false);
  ink_drop->SetShowHighlightOnFocus(false);
  return std::move(ink_drop);
}

void PaddedImageButton::OnThemeChanged() {
  ImageButton::OnThemeChanged();

  SetInkDropBaseColor(GetNativeTheme()->GetSystemColor(
      ui::NativeTheme::kColorId_PaddedButtonInkDropColor));
}

BEGIN_METADATA(PaddedImageButton, views::ImageButton)
END_METADATA

}  // namespace brave_ads
