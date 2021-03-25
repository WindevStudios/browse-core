/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_NOTIFICATION_BACKGROUND_PAINTER_H_
#define BRAVE_UI_BRAVE_ADS_NOTIFICATION_BACKGROUND_PAINTER_H_

#include "ui/gfx/color_palette.h"
#include "ui/views/painter.h"

namespace brave_ads {

// Background Painter for notifications with rounded corners. This draws the
// rectangle with rounded corners
class NotificationBackgroundPainter : public views::Painter {
 public:
  NotificationBackgroundPainter(const int top_radius,
                                const int bottom_radius,
                                const SkColor color = SK_ColorWHITE);
  ~NotificationBackgroundPainter() override;

  // views::Painter implementation
  gfx::Size GetMinimumSize() const override;
  void Paint(gfx::Canvas* canvas, const gfx::Size& size) override;

 private:
  const SkScalar top_radius_;
  const SkScalar bottom_radius_;
  const SkColor color_;

  gfx::Insets insets_;

  NotificationBackgroundPainter(const NotificationBackgroundPainter&) = delete;
  NotificationBackgroundPainter& operator=(
      const NotificationBackgroundPainter&) = delete;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_NOTIFICATION_BACKGROUND_PAINTER_H_
