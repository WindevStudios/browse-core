/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/core/bat_ledger_component.h"

#include "bat/ledger/internal/core/bat_ledger_test.h"

namespace ledger {

class BATLedgerComponentTest : public BATLedgerTest {};

class ComponentA : public BATLedgerComponent<ComponentA> {};
class ComponentB : public BATLedgerComponent<ComponentB> {};

TEST_F(BATLedgerComponentTest, ComponentLoading) {
  base::WeakPtr<ComponentA> weak_a;
  base::WeakPtr<ComponentB> weak_b;

  {
    BATLedgerContext context(GetTestLedgerClient());
    auto* a = context.Get<ComponentA>();
    auto* b = context.Get<ComponentB>();
    ASSERT_NE(static_cast<void*>(a), static_cast<void*>(b));
  }

  ASSERT_FALSE(static_cast<bool>(weak_a));
  ASSERT_FALSE(static_cast<bool>(weak_b));
}

}  // namespace ledger
