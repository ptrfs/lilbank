#pragma once

#include "./account.hpp"
#include "./bank.hpp"
#include <cstdlib>

bool pay_checking(int id_get, int id_pay, bank& drawee, account& payee, checking_account& drawer, bank& payee_bank,
         int amount) {
  // Open Account
  drawer.open_account();

  if (!drawee.check_id_exists(id_pay) || !payee_bank.check_id_exists(id_get)){
    return EXIT_FAILURE;
  }
  
  // Deposit into drawer
  if (!drawer.withdraw(amount)) {
    return EXIT_FAILURE;
  }

  payee.deposit(amount);
  return 0;
}
