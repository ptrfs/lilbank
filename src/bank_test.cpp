#include "bank.hpp"
#include "gtest/gtest.h"

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

// Entry point for running tests
int main(int argc, char **argv) {
  // Initialize Google Test framework
  ::testing::InitGoogleTest(&argc, argv);

  // Run tests
  return RUN_ALL_TESTS();
}
