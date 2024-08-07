#pragma once

#include "./bank.hpp"
#include <cstdlib>
#include <string>

class account {
protected:
  int balance;
  int id;
  std::string name;
  bank bank_member;

public:
  account(std::string name, bank &bank)
      : balance(1), name(name), bank_member(bank) {
    this->id = bank_member.add_customer();
  }

  virtual void deposit(int amount) { this->balance += amount; }

  virtual bool withdraw(int amount) {
    if (balance < amount) {
      return 1;
    }

    this->balance -= amount;
    return 0;
  }

  std::string get_name() const { return this->name; }

  int get_balance() const { return this->balance; }

  virtual ~account();
};

class checking_account : public account {
protected:
  int balance;

private:
  // 1 for open, 0 for closed
  bool status;

public:
  checking_account(std::string name, bank &bank)
      : account(name, bank), balance(0), status(false) {}

  void open_account() { this->status = true; }

  void close_account() { this->status = false; }

  virtual void deposit(int amount) override {
    if (this->status != 1)
      throw "Account not opened!";

    this->balance += amount;
  }

  virtual bool withdraw(int amount) override {
    if (this->status != 1)
      throw "Account in not opened!";

    if (balance < amount) {
      return EXIT_FAILURE;
    }

    this->balance -= amount;
    return false;
  }

  ~checking_account() override { this->status = false; }
};

class savings_account : public account {
private:
  int withdraw_limit = 1;

public:
  savings_account(std::string name, bank &bank)
      : account(name, bank), withdraw_limit(1) {}

  bool withdraw(int amount) {
    if (balance < amount || amount > withdraw_limit) {
      return true;
    }

    this->balance -= amount;
    return false;
  }

  // setting withdraw limit
  void set_withdraw_limit(int amount) { this->withdraw_limit = amount; }
};

class credit_account : public account {
private:
  unsigned int credit_limit = 10000;

public:
  credit_account(std::string name, bank &bank)
      : account(name, bank), credit_limit(10000) {}

  using account::withdraw;
  bool withdraw(unsigned int amount) {
    if (static_cast<unsigned int>(balance) < amount && credit_limit == 0) {
      return EXIT_FAILURE;
    } else if (static_cast<unsigned int>(balance) < amount &&
               credit_limit > amount) {
      amount -= credit_limit;
      return EXIT_SUCCESS;
    } else if (balance > static_cast<int>(amount)) {
      amount -= balance;
      return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
  }

  void deposit(int amount) override {
    if (this->credit_limit != 10000) {
      int deposit_amount = 0;

      if (this->credit_limit + amount > 10000) {
        deposit_amount = (this->credit_limit + amount);
        deposit_amount -= 10000;
        this->balance += deposit_amount;
        this->credit_limit += (amount - deposit_amount);
      }
    }

    this->balance += amount;
  }
};
