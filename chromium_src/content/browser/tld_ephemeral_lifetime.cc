/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "content/public/browser/tld_ephemeral_lifetime.h"

#include <map>

#include "base/no_destructor.h"
#include "services/network/public/mojom/cookie_manager.mojom.h"

namespace content {

namespace {

using TLDEphemeralLifetimeMap =
    std::map<TLDEphemeralLifetimeKey, base::WeakPtr<TLDEphemeralLifetime>>;

// This map allows TLDEphemeralLifetime to manage the lifetime of ephemeral
// storage. We use weak pointers so that we can catch misuse of more easily.
// With weak pointers, these entries will become null if they are destroyed,
// but not removed from the map.
TLDEphemeralLifetimeMap& active_tld_storage_areas() {
  static base::NoDestructor<TLDEphemeralLifetimeMap> active_storage_areas;
  return *active_storage_areas.get();
}

}  // namespace

TLDEphemeralLifetime::TLDEphemeralLifetime(TLDEphemeralLifetimeKey key,
                                           StoragePartition* storage_partition)
    : key_(std::move(key)), storage_partition_(storage_partition) {
  DCHECK(active_tld_storage_areas().find(key_) ==
         active_tld_storage_areas().end());
  DCHECK(storage_partition_);
  active_tld_storage_areas().emplace(key_, weak_factory_.GetWeakPtr());
}

TLDEphemeralLifetime::~TLDEphemeralLifetime() {
  auto filter = network::mojom::CookieDeletionFilter::New();
  filter->ephemeral_storage_domain = key_.second;
  storage_partition_->GetCookieManagerForBrowserProcess()->DeleteCookies(
      std::move(filter), base::NullCallback());

  if (!on_destroy_callbacks_.empty()) {
    auto on_destroy_callbacks = std::move(on_destroy_callbacks_);
    for (auto& callback : on_destroy_callbacks) {
      std::move(callback).Run(key_.second);
    }
  }

  active_tld_storage_areas().erase(key_);
}

scoped_refptr<TLDEphemeralLifetime> TLDEphemeralLifetime::Get(
    BrowserContext* browser_context,
    std::string storage_domain) {
  const TLDEphemeralLifetimeKey key(browser_context, std::move(storage_domain));
  return Get(key);
}

scoped_refptr<TLDEphemeralLifetime> TLDEphemeralLifetime::GetOrCreate(
    BrowserContext* browser_context,
    StoragePartition* storage_partition,
    std::string storage_domain) {
  TLDEphemeralLifetimeKey key(browser_context, std::move(storage_domain));
  if (scoped_refptr<TLDEphemeralLifetime> existing = Get(key)) {
    return existing;
  }

  return base::MakeRefCounted<TLDEphemeralLifetime>(std::move(key),
                                                    storage_partition);
}

// static
scoped_refptr<TLDEphemeralLifetime> TLDEphemeralLifetime::Get(
    const TLDEphemeralLifetimeKey& key) {
  auto it = active_tld_storage_areas().find(key);
  DCHECK(it == active_tld_storage_areas().end() || it->second.get());
  return it != active_tld_storage_areas().end() ? it->second.get() : nullptr;
}

const std::string& TLDEphemeralLifetime::GetStorageDomain() const {
  return key_.second;
}

void TLDEphemeralLifetime::RegisterOnDestroyCallback(
    OnDestroyCallback callback) {
  on_destroy_callbacks_.push_back(std::move(callback));
}

}  // namespace content
