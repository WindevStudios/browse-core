/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/notification_header_view.h"

#include <memory>

#include "brave/ui/brave_ads/public/cpp/constants.h"
#include "build/build_config.h"
#include "ui/gfx/color_palette.h"
#include "ui/gfx/font_list.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/flex_layout.h"
#include "ui/views/layout/flex_layout_types.h"
#include "ui/views/metadata/metadata_impl_macros.h"
#include "ui/views/view_class_properties.h"

namespace brave_ads {

namespace {

const int kHeaderHeight = 24;

constexpr gfx::Insets kMargin(0, 2, 0, 2);
constexpr gfx::Insets kInteriorMargin(2, 2, 0, 2);

constexpr gfx::Insets kDefaultBorderInsets(9, 12, 6, 0);

const int kTitleFontSize = 14;
constexpr SkColor kTitleColor = SkColorSetRGB(0x75, 0x75, 0x75);

const int kControlButtonSpacing = 10;

gfx::FontList GetFontList(const int font_size) {
  gfx::Font default_font;
  const int font_size_delta = font_size - default_font.GetFontSize();
  const gfx::Font font = default_font.Derive(font_size_delta, gfx::Font::NORMAL,
                                             gfx::Font::Weight::SEMIBOLD);
  return gfx::FontList(font);
}

gfx::Insets CalculateBorderInsets(const int font_list_height) {
#if defined(OS_WIN)
  // On Windows, the fonts can have slightly different metrics reported,
  // depending on where the code runs. In Chrome, DirectWrite is on, which means
  // font metrics are reported from Skia, which rounds from float using ceil.
  // In unit tests, however, GDI is used to report metrics, and the height
  // reported there is consistent with other platforms. This means there is a
  // difference of 1px in height between Chrome on Windows and everything else
  // (where everything else includes unit tests on Windows). This 1px causes the
  // text and everything else to stop aligning correctly, so we account for it
  // by shrinking the top padding by 1
  if (font_list_height != 15) {
    return kDefaultBorderInsets - gfx::Insets(/* top */ 1, 0, 0, 0);
  }
#endif

  return kDefaultBorderInsets;
}

views::Label* CreateLabel(const int font_size) {
  views::Label* label = new views::Label();

  const gfx::FontList font_list = GetFontList(font_size);
  label->SetFontList(font_list);

  const int font_list_height = font_list.GetHeight();
  label->SetLineHeight(font_list_height);

  label->SetHorizontalAlignment(gfx::ALIGN_LEFT);

  const gfx::Insets border_insets(CalculateBorderInsets(font_list_height));
  label->SetBorder(views::CreateEmptyBorder(border_insets));

  return label;
}

}  // namespace

NotificationHeaderView::NotificationHeaderView(PressedCallback callback)
    : views::Button(callback) {
  BuildView();
}

NotificationHeaderView::~NotificationHeaderView() = default;

void NotificationHeaderView::SetTitle(const base::string16& text) {
  DCHECK(title_label_);

  title_label_->SetText(text);
}

void NotificationHeaderView::SetTitleElideBehavior(
    gfx::ElideBehavior elide_behavior) {
  DCHECK(title_label_);

  title_label_->SetElideBehavior(elide_behavior);
}

///////////////////////////////////////////////////////////////////////////////

void NotificationHeaderView::BuildView() {
  views::FlexLayout* layout_manager =
      SetLayoutManager(std::make_unique<views::FlexLayout>());
  layout_manager->SetDefault(views::kMarginsKey, kMargin);
  layout_manager->SetInteriorMargin(kInteriorMargin);
  layout_manager->SetCollapseMargins(true);

  const gfx::Size size = gfx::Size(kNotificationWidth, kHeaderHeight);
  SetPreferredSize(size);

  title_label_ = CreateTitleLabel();
  AddChildView(title_label_);

  views::View* control_button_spacing_view =
      CreateSpacerView(kControlButtonSpacing);
  AddChildView(control_button_spacing_view);
}

views::Label* NotificationHeaderView::CreateTitleLabel() {
  views::Label* label = CreateLabel(kTitleFontSize);

  label->SetEnabledColor(kTitleColor);
  label->SetBackgroundColor(SK_ColorTRANSPARENT);

  const views::FlexSpecification flex_specification =
      views::FlexSpecification(views::MinimumFlexSizeRule::kScaleToZero,
                               views::MaximumFlexSizeRule::kPreferred);
  label->SetProperty(views::kFlexBehaviorKey, flex_specification);

  return label;
}

views::View* NotificationHeaderView::CreateSpacerView(const int spacing) {
  views::View* view = new views::View;

  const gfx::Size size = gfx::Size(spacing, kHeaderHeight);
  view->SetPreferredSize(size);

  const views::FlexSpecification flex_specification =
      views::FlexSpecification(views::MinimumFlexSizeRule::kScaleToMinimum,
                               views::MaximumFlexSizeRule::kUnbounded);
  view->SetProperty(views::kFlexBehaviorKey, flex_specification);

  return view;
}

BEGIN_METADATA(NotificationHeaderView, views::Button)
END_METADATA

}  // namespace brave_ads
