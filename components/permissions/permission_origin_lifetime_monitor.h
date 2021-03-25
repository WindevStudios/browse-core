/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_PERMISSIONS_PERMISSION_ORIGIN_LIFETIME_MONITOR_H_
#define BRAVE_COMPONENTS_PERMISSIONS_PERMISSION_ORIGIN_LIFETIME_MONITOR_H_

#include <string>

#include "base/callback.h"
#include "components/permissions/permission_request_id.h"
#include "url/gurl.h"

namespace permissions {

// An interface to enable support for an origin-based permission lifetime logic.
class PermissionOriginLifetimeMonitor {
 public:
  virtual ~PermissionOriginLifetimeMonitor() = default;

  // Set a callback to call when a permission origin is destroyed.
  // Callback will receive a string returned by
  // |SubscribeToPermissionOriginDestruction|.
  virtual void SetOnPermissionOriginDestroyedCallback(
      base::RepeatingCallback<void(const std::string&)> callback) = 0;

  // Subscribe to a permission origin destruction. Should return a string key
  // which will be used in a callback. An empty key can be returned if
  // a permission origin can not be observed, for example if |requesting_origin|
  // doesn't match current origin in a tab |request_id| refers to.
  virtual std::string SubscribeToPermissionOriginDestruction(
      const PermissionRequestID& request_id,
      const GURL& requesting_origin) = 0;
};

}  // namespace permissions

#endif  // BRAVE_COMPONENTS_PERMISSIONS_PERMISSION_ORIGIN_LIFETIME_MONITOR_H_
