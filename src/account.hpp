#include "./bank.hpp"
#include <memory>
#include <string>

class account {
private:
  int id;
  std::string name;
  bank bank_member;

protected:
  int balance;

public:
  account(std::string name, bank bank)
      : name(name), bank_member(bank), balance(1) {
    this->id = bank_member.add_customer();
  }

  void deposit(int amount) { this->balance += amount; }

  bool withdraw(int amount) {
    if (balance < amount) {
      return EXIT_FAILURE;
    }

    this->balance -= amount;
    return 0;
  }
};

class checking_account : account {};

class credit_account : account {
public:
  void withdraw(int amount) { this->balance -= amount; }
};

class savings_account : account {
private:
  int withdraw_limit = 100;

public:
  bool withdraw(int amount) {
    if (balance < amount || amount > withdraw_limit) {
      return EXIT_FAILURE;
    }

    this->balance -= amount;
    return false;
  }

  // setting withdraw limit
  void set_withdraw_limit (int amount){
    this->withdraw_limit = amount;
  }
};
