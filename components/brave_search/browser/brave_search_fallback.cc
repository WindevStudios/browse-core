/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_search/browser/brave_search_fallback.h"

#include <utility>

namespace brave_search {

BraveSearchFallback::BraveSearchFallback() : weak_factory_(this) {}

BraveSearchFallback::~BraveSearchFallback() {}

void BraveSearchFallback::FetchBackupResults(
    const std::string& query_string,
    const std::string& lang,
    const std::string& country,
    const std::string& geo,
    FetchBackupResultsCallback callback) {
  // TODO(sergz): make a call to fetch a response and remove that callback call
  std::move(callback).Run("response");
}

void BraveSearchFallback::OnFetchBackupResults(
    FetchBackupResultsCallback callback,
    const std::string& response) {
  std::move(callback).Run(response);
}

}  // namespace brave_search
