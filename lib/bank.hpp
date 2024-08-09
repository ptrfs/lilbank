#pragma once

#include "files.hpp"
#include <algorithm>
#include <filesystem>
#include <optional>
#include <random>
#include <string>
#include <vector>

// Get an id (random integer) in the bounds of `limit`
static int get_id(int limit) {
  std::random_device random_device;
  std::mt19937 gen(random_device());
  std::uniform_int_distribution<int> dis(1, limit);

  return (int)(dis(gen));
}

class bank {
private:
  std::string name;
  int id;
  int interest_rate = 1;

  // Identfies, in integer format, the customers in the bank (class)
  std::vector<signed int> customer_ids;

public:
  bank(std::string name, std::string home_dir_name)
      : name(name), id(get_id(300)) {
    create_lilbank(home_dir_name, std::nullopt);
    std::string base_path =
        "/home/" + home_dir_name + "/.local/lilbank/" + name;

    std::filesystem::create_directory(base_path);
    std::filesystem::create_directory(base_path + "/saving");
    std::filesystem::create_directory(base_path + "/debit");
    std::filesystem::create_directory(base_path + "/credit");
  }

  // Get the amount of customers in a bank
  int get_customer_amount() { return this->customer_ids.size(); }

  // Setting and Getting
  void set_interest_rate(int new_interest_rate) {
    this->interest_rate = new_interest_rate;
  }

  std::string get_name() { return this->name; }

  bool check_id_exists(int id) {
    auto id_exists =
        std::find(this->customer_ids.begin(), this->customer_ids.end(), id);

    return (id_exists != this->customer_ids.end());
  }

  int add_customer() {
    int customer_id = get_id(8000000);

    this->customer_ids.push_back(customer_id);
    return customer_id;
  }
};
