/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/ui/brave_ads/public/cpp/notification.h"

namespace brave_ads {

Notification::Notification(const std::string& id,
                           const base::string16& title,
                           const base::string16& body,
                           scoped_refptr<NotificationDelegate> delegate)
    : id_(id), title_(title), body_(body), delegate_(std::move(delegate)) {}

Notification::Notification(scoped_refptr<NotificationDelegate> delegate,
                           const Notification& other)
    : Notification(other) {
  delegate_ = delegate;
}

Notification::Notification(const std::string& id, const Notification& other)
    : Notification(other) {
  id_ = id;
}

Notification::Notification(const Notification& other) = default;

Notification& Notification::operator=(const Notification& other) = default;

Notification::~Notification() = default;

}  // namespace brave_ads
