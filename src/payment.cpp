#pragma once

#include "./bank.hpp"
#include "./account.hpp"

bool pay (int id_get, int id_pay, bank bank) {
  if (!bank.check_id_exists(id_get) || (!bank.check_id_exists(id_pay)))
    return 1;
  
}
