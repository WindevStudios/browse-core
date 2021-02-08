/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_
#define BRAVE_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_

#define BRAVE_HISTOGRAM_VALUES                                             \
  BRAVE_START = 600, BRAVE_AD_BLOCKED, BRAVE_WALLET_CREATED,               \
  BRAVE_ON_WALLET_PROPERTIES, BRAVE_ON_PUBLISHER_DATA,                     \
  BRAVE_ON_CURRENT_REPORT, BRAVE_ON_BRAVE_THEME_TYPE_CHANGED,              \
  BRAVE_REWARDS_NOTIFICATION_ADDED, BRAVE_REWARDS_NOTIFICATION_DELETED,    \
  BRAVE_REWARDS_ALL_NOTIFICATIONS_DELETED, BRAVE_REWARDS_GET_NOTIFICATION, \
  BRAVE_REWARDS_GET_ALL_NOTIFICATIONS, BRAVE_WALLET_FAILED,                \
  BRAVE_PLAYLIST_ON_PLAYLIST_ITEM_STATUS_CHANGED,

#include "../../../../extensions/browser/extension_event_histogram_value.h"  // NOLINT

#undef BRAVE_HISTOGRAM_VALUES

#endif  // BRAVE_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_EVENT_HISTOGRAM_VALUE_H_
