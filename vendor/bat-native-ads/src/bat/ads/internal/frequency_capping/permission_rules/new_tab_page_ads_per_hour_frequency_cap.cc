/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/permission_rules/new_tab_page_ads_per_hour_frequency_cap.h"

#include <cstdint>
#include <deque>

#include "base/time/time.h"
#include "bat/ads/internal/features/ad_serving/ad_serving_features.h"
#include "bat/ads/internal/frequency_capping/frequency_capping_util.h"

namespace ads {

NewTabPageAdsPerHourFrequencyCap::NewTabPageAdsPerHourFrequencyCap(
    const AdEventList& ad_events)
    : ad_events_(ad_events) {}

NewTabPageAdsPerHourFrequencyCap::~NewTabPageAdsPerHourFrequencyCap() = default;

bool NewTabPageAdsPerHourFrequencyCap::ShouldAllow() {
  const AdEventList filtered_ad_events = FilterAdEvents(ad_events_);
  if (!DoesRespectCap(filtered_ad_events)) {
    last_message_ = "You have exceeded the allowed new tab page ads per hour";
    return false;
  }

  return true;
}

std::string NewTabPageAdsPerHourFrequencyCap::get_last_message() const {
  return last_message_;
}

bool NewTabPageAdsPerHourFrequencyCap::DoesRespectCap(
    const AdEventList& ad_events) {
  const std::deque<uint64_t> history =
      GetTimestampHistoryForAdEvents(ad_events);

  const uint64_t time_constraint = base::Time::kSecondsPerHour;

  const uint64_t cap = features::GetMaximumNewTabPageAdsPerHour();

  return DoesHistoryRespectCapForRollingTimeConstraint(history, time_constraint,
                                                       cap);
}

AdEventList NewTabPageAdsPerHourFrequencyCap::FilterAdEvents(
    const AdEventList& ad_events) const {
  AdEventList filtered_ad_events = ad_events;

  const auto iter = std::remove_if(
      filtered_ad_events.begin(), filtered_ad_events.end(),
      [](const AdEventInfo& ad_event) {
        return ad_event.type != AdType::kNewTabPageAd ||
               ad_event.confirmation_type != ConfirmationType::kViewed;
      });

  filtered_ad_events.erase(iter, filtered_ad_events.end());

  return filtered_ad_events;
}

}  // namespace ads
