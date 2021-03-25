/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_UI_BRAVE_ADS_PUBLIC_CPP_NOTIFICATION_H_
#define BRAVE_UI_BRAVE_ADS_PUBLIC_CPP_NOTIFICATION_H_

#include <string>
#include <utility>

#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "brave/ui/brave_ads/public/cpp/brave_ads_public_export.h"
#include "brave/ui/brave_ads/public/cpp/notification_delegate.h"

namespace brave_ads {

class BRAVE_ADS_PUBLIC_EXPORT Notification {
 public:
  // Create a new notification with an |id|, |title| text and |body| text.
  // |delegate| will influence the behaviour of this notification and receives
  // events on its behalf. The delegate may be omitted
  Notification(const std::string& id,
               const base::string16& title,
               const base::string16& body,
               scoped_refptr<NotificationDelegate> delegate);

  // Creates a copy of the |other| notification. The delegate, if any, will be
  // identical for both the notification instances. The |id| of the notification
  // will be replaced by the given value
  Notification(const std::string& id, const Notification& other);

  // Creates a copy of the |other| notification. The delegate will be replaced
  // by |delegate|
  Notification(scoped_refptr<NotificationDelegate> delegate,
               const Notification& other);

  // Creates a copy of the |other| notification. The delegate, if any, will be
  // identical for both the notification instances
  Notification(const Notification& other);

  Notification& operator=(const Notification& other);

  virtual ~Notification();

  const std::string& id() const { return id_; }

  const base::string16& title() const { return title_; }
  void set_title(const base::string16& title) { title_ = title; }

  const base::string16& body() const { return body_; }
  void set_body(const base::string16& body) { body_ = body; }

  NotificationDelegate* delegate() const { return delegate_.get(); }

  void set_delegate(scoped_refptr<NotificationDelegate> delegate) {
    DCHECK(!delegate_);
    delegate_ = std::move(delegate);
  }

 protected:
  std::string id_;

  base::string16 title_;
  base::string16 body_;

 private:
  // A proxy object that allows access back to the JavaScript object that
  // represents the notification, for firing events
  scoped_refptr<NotificationDelegate> delegate_;
};

}  // namespace brave_ads

#endif  // BRAVE_UI_BRAVE_ADS_PUBLIC_CPP_NOTIFICATION_H_
