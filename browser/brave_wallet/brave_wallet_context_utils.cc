/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_wallet/brave_wallet_context_utils.h"
#include "chrome/browser/profiles/profile.h"

namespace brave_wallet {

bool IsAllowedForProfile(Profile* profile) {
  if (profile && profile->IsTor())
    return false;

  return true;
}

}  // namespace brave_wallet
