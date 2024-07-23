#pragma once

#include "./bank.hpp"
#include <cstdlib>
#include <string>

enum account_class {
  basic,
  checking,
  savings,
  credit,
};

class account {
protected:
  int balance;
  int id;
  std::string name;
  account_class class_type = basic;
  bank bank_member;

public:
  account(std::string name, bank &bank)
      : name(name), bank_member(bank), balance(1) {
    this->id = bank_member.add_customer();
  }

  virtual void deposit(int amount) { this->balance += amount; }

  virtual bool withdraw(int amount) {
    if (balance < amount) {
      return false;
    }

    this->balance -= amount;
    return 1;
  }

  std::string get_name() { return this->name; }

  int get_balance() { return this->balance; }
};

class checking_account : account {
protected:
  int balance;

private:
  // 1 for open, 0 for closed
  int status;
  account_class class_type = checking;

public:
  void open_account() { this->status = true; }

  void close_account() { this->status = false; }

  void deposit(int amount) {
    if (this->status != 1)
      throw "Account not opened!";

    this->balance += amount;
  }

  bool withdraw(int amount) {
    if (this->status != 1)
      throw "Account in not opened!";

    if (balance < amount) {
      return EXIT_FAILURE;
    }

    this->balance -= amount;
    return false;
  }

  ~checking_account() { this->status = false; }
};

class savings_account : account {
private:
  int withdraw_limit = 1;
  account_class class_type = savings;

public:
  bool withdraw(int amount) {
    if (balance < amount || amount > withdraw_limit) {
      return EXIT_FAILURE;
    }

    this->balance -= amount;
    return false;
  }

  // setting withdraw limit
  void set_withdraw_limit(int amount) { this->withdraw_limit = amount; }
};
