#include <string>
#include <./bank.hpp>
#include <memory>

class account {
private:
  int id;
  std::string name;
  bank bank_member;

protected:
  int balance;

public:
  account(std::string name, bank bank): name(name), bank_member(bank), balance(1) {
    this->id = bank_member.add_customer();
  }

  void deposit(int amount) {
    this->balance += amount;
  }

  bool withdraw(int amount) {
    if (balance < amount){
      return EXIT_FAILURE;
    }

    this->balance -= amount;
  }
};

class checking_account: account {};

class credit_account: account {
public:
  bool withdraw(int amount) {
    this->balance -= amount;
  }
};

class savings_account: account {
private:
  int withdraw_limit = 1;

public:
  bool withdraw(int amount) {
    if (balance < amount || amount > withdraw_limit){
      return EXIT_FAILURE;
    }

    this->balance -= amount;
  }

};
