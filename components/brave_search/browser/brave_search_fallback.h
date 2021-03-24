/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_SEARCH_BROWSER_BRAVE_SEARCH_FALLBACK_H_
#define BRAVE_COMPONENTS_BRAVE_SEARCH_BROWSER_BRAVE_SEARCH_FALLBACK_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "brave/components/brave_search/common/brave_search.mojom.h"

namespace brave_search {

class BraveSearchFallback final
    : public brave_search::mojom::BraveSearchFallback {
 public:
  BraveSearchFallback(const BraveSearchFallback&) = delete;
  BraveSearchFallback& operator=(const BraveSearchFallback&) = delete;
  BraveSearchFallback();
  ~BraveSearchFallback() override;

  void FetchBackupResults(const std::string& query_string,
                          const std::string& lang,
                          const std::string& country,
                          const std::string& geo,
                          FetchBackupResultsCallback callback) override;
  void OnFetchBackupResults(FetchBackupResultsCallback callback,
                            const std::string& response);

 private:
  base::WeakPtrFactory<BraveSearchFallback> weak_factory_;
};

}  // namespace brave_search

#endif  // BRAVE_COMPONENTS_BRAVE_SEARCH_BROWSER_BRAVE_SEARCH_FALLBACK_H_
