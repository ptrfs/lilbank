#pragma once

#include "./account.hpp"
#include "./bank.hpp"

bool pay(int id_get, int id_pay, bank& drawee, account& payee, account& drawer,
         int amount) {
  if (!drawee.check_id_exists(id_get) || (!drawee.check_id_exists(id_pay)))
    return 1;

  if (!drawer.withdraw(amount))
    return 1;

  payee.deposit(amount);

  return 0;
}
