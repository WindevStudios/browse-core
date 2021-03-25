/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/notification_control_buttons_view.h"

#include <memory>

#include "base/bind.h"
#include "brave/app/vector_icons/vector_icons.h"
#include "brave/ui/brave_ads/notification_view.h"
#include "brave/ui/brave_ads/padded_image_button.h"
#include "brave/ui/brave_ads/padded_image_view.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/color_palette.h"
#include "ui/gfx/paint_vector_icon.h"
#include "ui/views/background.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/metadata/metadata_impl_macros.h"

namespace brave_ads {

namespace {
constexpr SkColor kCloseButtonIconColor = SkColorSetRGB(0x4c, 0x36, 0xd2);
}  // namespace

NotificationControlButtonsView::NotificationControlButtonsView(
    NotificationView* notification_view)
    : notification_view_(notification_view) {
  DCHECK(notification_view_);

  views::BoxLayout* layout_manager =
      SetLayoutManager(std::make_unique<views::BoxLayout>(
          views::BoxLayout::Orientation::kHorizontal));

  layout_manager->set_cross_axis_alignment(
      views::BoxLayout::CrossAxisAlignment::kStart);

  // Use layer to change the opacity
  SetPaintToLayer();
  layer()->SetFillsBoundsOpaquely(false);
}

NotificationControlButtonsView::~NotificationControlButtonsView() = default;

void NotificationControlButtonsView::ShowInfoButton(const bool should_show) {
  if (should_show && !info_button_) {
    info_button_ = AddChildView(std::make_unique<PaddedImageView>());

    gfx::ImageSkia image_skia =
        gfx::CreateVectorIcon(kBraveAdsInfoIcon, SK_ColorTRANSPARENT);

    info_button_->SetImage(image_skia);

    info_button_->SetBackground(
        views::CreateSolidBackground(SK_ColorTRANSPARENT));

    Layout();
  } else if (!should_show && info_button_) {
    DCHECK(Contains(info_button_));
    RemoveChildViewT(info_button_);
    info_button_ = nullptr;
  }
}

void NotificationControlButtonsView::ShowCloseButton(const bool should_show) {
  if (should_show && !close_button_) {
    close_button_ = AddChildView(std::make_unique<PaddedImageButton>(
        base::BindRepeating(&NotificationView::OnCloseButtonPressed,
                            base::Unretained(notification_view_))));

    close_button_->SetImage(
        views::Button::STATE_NORMAL,
        gfx::CreateVectorIcon(kBraveAdsCloseButtonIcon, kCloseButtonIconColor));

    close_button_->SetBackground(
        views::CreateSolidBackground(SK_ColorTRANSPARENT));

    Layout();
  } else if (!should_show && close_button_) {
    DCHECK(Contains(close_button_));
    RemoveChildViewT(close_button_);
    close_button_ = nullptr;
  }
}

void NotificationControlButtonsView::ShowButtons(const bool should_show) {
  DCHECK(layer());

  // Manipulate the opacity instead of changing the visibility to keep the tab
  // order even when the view is invisible
  layer()->SetOpacity(should_show ? 1.0 : 0.0);

  SetCanProcessEventsWithinSubtree(should_show);
}

BEGIN_METADATA(NotificationControlButtonsView, views::View)
END_METADATA

}  // namespace brave_ads
