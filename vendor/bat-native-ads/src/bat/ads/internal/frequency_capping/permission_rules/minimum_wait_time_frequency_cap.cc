/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/permission_rules/minimum_wait_time_frequency_cap.h"

#include <cstdint>
#include <deque>

#include "base/time/time.h"
#include "bat/ads/internal/frequency_capping/frequency_capping_util.h"
#include "bat/ads/internal/platform/platform_helper.h"
#include "bat/ads/internal/settings/settings.h"

namespace ads {

namespace {
const uint64_t kMinimumWaitTimeFrequencyCap = 1;
}  // namespace

MinimumWaitTimeFrequencyCap::MinimumWaitTimeFrequencyCap(
    const AdEventList& ad_events)
    : ad_events_(ad_events) {}

MinimumWaitTimeFrequencyCap::~MinimumWaitTimeFrequencyCap() = default;

bool MinimumWaitTimeFrequencyCap::ShouldAllow() {
  if (PlatformHelper::GetInstance()->IsMobile()) {
    return true;
  }

  const AdEventList filtered_ad_events = FilterAdEvents(ad_events_);
  if (!DoesRespectCap(filtered_ad_events)) {
    last_message_ = "Ad cannot be shown as minimum wait time has not passed";
    return false;
  }

  return true;
}

std::string MinimumWaitTimeFrequencyCap::get_last_message() const {
  return last_message_;
}

bool MinimumWaitTimeFrequencyCap::DoesRespectCap(const AdEventList& ad_events) {
  const std::deque<uint64_t> history =
      GetTimestampHistoryForAdEvents(ad_events);

  const uint64_t ads_per_hour = settings::GetAdsPerHour();

  const uint64_t time_constraint = base::Time::kSecondsPerHour / ads_per_hour;

  return DoesHistoryRespectCapForRollingTimeConstraint(
      history, time_constraint, kMinimumWaitTimeFrequencyCap);
}

AdEventList MinimumWaitTimeFrequencyCap::FilterAdEvents(
    const AdEventList& ad_events) const {
  AdEventList filtered_ad_events = ad_events;

  const auto iter = std::remove_if(
      filtered_ad_events.begin(), filtered_ad_events.end(),
      [](const AdEventInfo& ad_event) {
        return ad_event.type != AdType::kAdNotification ||
               ad_event.confirmation_type != ConfirmationType::kViewed;
      });

  filtered_ad_events.erase(iter, filtered_ad_events.end());

  return filtered_ad_events;
}

}  // namespace ads
