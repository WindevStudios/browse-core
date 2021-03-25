/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/exclusion_rules/anti_targeting_frequency_cap.h"

#include <algorithm>
#include <memory>

#include "base/strings/stringprintf.h"
#include "bat/ads/internal/ad_targeting/resources/frequency_capping/anti_targeting_resource.h"
#include "bat/ads/internal/bundle/creative_ad_info.h"
#include "bat/ads/internal/url_util.h"

namespace ads {

namespace {
bool HasVisitedSiteOnAntiTargetingList(
    const BrowsingHistoryList history_sites,
    const AnitTargetingList anti_targeting_sites) {
  for (const auto& site_lhs : anti_targeting_sites) {
    for (const auto& site_rhs : history_sites) {
      if (SameDomainOrHost(site_lhs, site_rhs)) {
        return true;
      }
    }
  }

  return false;
}

}  // namespace

AntiTargetingFrequencyCap::AntiTargetingFrequencyCap(
    resource::AntiTargeting* anti_targeting,
    const BrowsingHistoryList& history)
    : anti_targeting_(anti_targeting), history_(history) {}

AntiTargetingFrequencyCap::~AntiTargetingFrequencyCap() = default;

bool AntiTargetingFrequencyCap::ShouldExclude(const CreativeAdInfo& ad) {
  if (!DoesRespectCap(ad)) {
    last_message_ = base::StringPrintf(
        "creativeSetId %s excluded as user has "
        "previously visited an anti-targeting site",
        ad.creative_set_id.c_str());

    return true;
  }

  return false;
}

std::string AntiTargetingFrequencyCap::get_last_message() const {
  return last_message_;
}

bool AntiTargetingFrequencyCap::DoesRespectCap(const CreativeAdInfo& ad) const {
  if (history_.empty()) {
    return true;
  }

  AntiTargetingInfo anti_targeting = anti_targeting_->get();
  const auto iter = anti_targeting.sites.find(ad.creative_set_id);
  // Always respect if creative set has no anti-targeting sites
  if (iter == anti_targeting.sites.end()) {
    return true;
  }

  return !HasVisitedSiteOnAntiTargetingList(history_, iter->second);
}

}  // namespace ads
