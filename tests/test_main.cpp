#include "../src/payment.cpp"
#include "account.hpp"
#include "bank.hpp"
#include "gtest/gtest.h"
#include <memory>

// Test fixture for bank class
class BankTest : public ::testing::Test {
protected:
  // Set up the test fixture
  void SetUp() override {
    // Initialize bank
    bank_obj = new bank("Test Bank");
  }

  // Tear down the test fixture
  void TearDown() override {
    // Clean up
    delete bank_obj;
  }

  // Pointer to the bank object
  bank *bank_obj;
};

// Test fixture for account class
class AccountTest : public ::testing::Test {
private:
  std::unique_ptr<bank> test_bank = std::make_unique<bank>("test bank");

protected:
  void SetUp() override {
    account_obj = new account("Test Account", *test_bank);
  }

  void TearDown() override { delete account_obj; }

  account *account_obj;
};

// Test the constructor of the bank class
TEST_F(BankTest, ConstructorTest) {
  // Check if bank object is not null
  ASSERT_NE(bank_obj, nullptr);

  // Check if bank name is correctly set
  EXPECT_EQ(bank_obj->get_name(), "Test Bank");
}

// Test the add_customer method of the bank class
TEST_F(BankTest, AddCustomerTest) {
  // Add a customer
  bank_obj->add_customer();

  // Check if customer amount increased
  EXPECT_EQ(bank_obj->get_customer_amount(), 1);
}

// Example of more tests can be added here
TEST_F(AccountTest, ConstructorTest) {
  // Check if the account class is not null
  ASSERT_NE(account_obj, nullptr);

  // Check if the account name is true
  EXPECT_EQ(account_obj->get_name(), "Test Account");

  // Check if the account balance is true
  EXPECT_EQ(account_obj->get_balance(), 1);
}

TEST_F(AccountTest, DepositTest) {
  account_obj->deposit(10);
  EXPECT_EQ(account_obj->get_balance(), (10 + 1));
}

TEST_F(AccountTest, WithdrawTest) {
  std::unique_ptr<bank> b = std::make_unique<bank>("Test Bank");
  std::unique_ptr<account> a = std::make_unique<account>("Test Account", *b);
  a->deposit(100);
  EXPECT_FALSE(a->withdraw(200));

  EXPECT_TRUE(a->withdraw(50));
  EXPECT_EQ(a->get_balance(), (1 + 100 - 50));
}

// Entry point for running tests
int main(int argc, char **argv) {
  // Initialize Google Test framework
  ::testing::InitGoogleTest(&argc, argv);

  // Run tests
  return RUN_ALL_TESTS();
}