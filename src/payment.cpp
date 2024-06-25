#pragma once

#include "../lib/bank.hpp"
#include "../lib/account.hpp"
#include <cstdlib>

bool pay_checking(int id_get, int id_pay, bank &drawee, checking_account &payee,
                  checking_account &drawer, bank &payee_bank, int amount) {
  // Open Account
  drawer.open_account();
  payee.open_account();

  if (!drawee.check_id_exists(id_pay) || !payee_bank.check_id_exists(id_get)) {
    return EXIT_FAILURE;
  }

  // Deposit into drawer
  if (!drawer.withdraw(amount)) {
    return EXIT_FAILURE;
  }

  payee.deposit(amount);

  drawer.close_account();
  payee.close_account();

  return 0;
}

bool pay(int id_get, int id_pay, bank &drawee, account &payee, account &drawer,
         bank &payee_bank, int amount) {
  // Open Account
  if (!drawee.check_id_exists(id_pay) || !payee_bank.check_id_exists(id_get)) {
    return EXIT_FAILURE;
  }

  // Deposit into drawer
  if (!drawer.withdraw(amount)) {
    return EXIT_FAILURE;
  }

  payee.deposit(amount);

  return 0;
}

// bool pay_credit(int id_get, int id_pay, bank &drawee, credit_account &payee, account &drawer, bank &payee_bank, int amount) {

// }
