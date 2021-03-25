/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_FREQUENCY_CAPPING_ANTI_TARGETING_INFO_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_FREQUENCY_CAPPING_ANTI_TARGETING_INFO_H_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

namespace ads {

using AnitTargetingList = std::vector<std::string>;
using AntiTargetingMap = std::map<std::string, AnitTargetingList>;

struct AntiTargetingInfo {
 public:
  AntiTargetingInfo();
  AntiTargetingInfo(const AntiTargetingInfo& info);
  ~AntiTargetingInfo();

  uint16_t version = 0;
  // TODO(Moritz Haller): think about naming
  AntiTargetingMap sites;
};

}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_FREQUENCY_CAPPING_ANTI_TARGETING_INFO_H_
