/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_BAT_LEDGER_COMPONENT_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_BAT_LEDGER_COMPONENT_H_

#include "base/memory/weak_ptr.h"
#include "bat/ledger/internal/core/bat_ledger_context.h"

namespace ledger {

// Convenience class for defining BATLedgerContext components.
//
// Example:
//   class MyComponent : public BATLedgerComponent<MyComponent> {};
template <typename T>
class BATLedgerComponent : public BATLedgerContext::Object,
                           public base::SupportsWeakPtr<T> {
 public:
  static const BATLedgerContext::ComponentKey kComponentKey;
};

template <typename T>
const BATLedgerContext::ComponentKey BATLedgerComponent<T>::kComponentKey;

}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_BAT_LEDGER_COMPONENT_H_
