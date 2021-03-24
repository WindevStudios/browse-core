/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/permissions/chrome_permission_origin_lifetime_monitor.h"

#include "base/stl_util.h"
#include "brave/browser/ephemeral_storage/ephemeral_storage_tab_helper.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "net/base/url_util.h"

namespace permissions {

ChromePermissionOriginLifetimeMonitor::ChromePermissionOriginLifetimeMonitor() =
    default;

ChromePermissionOriginLifetimeMonitor::
    ~ChromePermissionOriginLifetimeMonitor() = default;

void ChromePermissionOriginLifetimeMonitor::
    SetOnPermissionOriginDestroyedCallback(
        base::RepeatingCallback<void(const std::string&)> callback) {
  permission_destroyed_callback_ = std::move(callback);
}

std::string
ChromePermissionOriginLifetimeMonitor::SubscribeToPermissionOriginDestruction(
    const PermissionRequestID& request_id,
    const GURL& requesting_origin) {
  DCHECK(permission_destroyed_callback_);
  auto* rfh = content::RenderFrameHost::FromID(request_id.render_process_id(),
                                               request_id.render_frame_id());
  if (!rfh) {
    return std::string();
  }
  auto* web_contents = content::WebContents::FromRenderFrameHost(rfh);
  if (!web_contents) {
    return std::string();
  }
  auto* ephemeral_storage_tab_helper =
      ephemeral_storage::EphemeralStorageTabHelper::FromWebContents(
          web_contents);
  DCHECK(ephemeral_storage_tab_helper);
  const std::string& storage_domain =
      ephemeral_storage_tab_helper->GetStorageDomain();
  const bool is_storage_domain_acceptable =
      requesting_origin.DomainIs(storage_domain) ||
      storage_domain == net::URLToEphemeralStorageDomain(requesting_origin);
  if (!is_storage_domain_acceptable) {
    // A different domain is currently in use in a WebContents connected to this
    // permission request, so it doesn't make sense to observe it and the
    // permission should be reset immediately.
    return std::string();
  }

  if (!base::Contains(active_subscriptions_, storage_domain)) {
    ephemeral_storage_tab_helper->RegisterOnStorageDomainDestroyedCallback(
        base::BindOnce(
            &ChromePermissionOriginLifetimeMonitor::OnEphemeralTLDDestroyed,
            weak_ptr_factory_.GetWeakPtr()));
    active_subscriptions_.insert(storage_domain);
  }
  return storage_domain;
}

void ChromePermissionOriginLifetimeMonitor::OnEphemeralTLDDestroyed(
    const std::string& storage_domain) {
  if (!permission_destroyed_callback_) {
    return;
  }
  DCHECK(base::Contains(active_subscriptions_, storage_domain));
  permission_destroyed_callback_.Run(storage_domain);
  active_subscriptions_.erase(storage_domain);
}

}  // namespace permissions
