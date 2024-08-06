#pragma once

// #include "toml.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

// App startup function to check if there is ~/.local/lilbank/, if not, create
// it
bool create_lilbank(std::string home_name, std::optional<std::string> custom_dir) {
  std::string dir;

  if (custom_dir.has_value()) {
    dir = custom_dir.value();
  } else {
    dir = "/home/" + home_name + "/.local/lilbank/";
  }

  try {
    std::filesystem::create_directory(dir);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  }
  return 0;
}

// Checks if a file exists
bool file_exists(std::string name) {
  std::fstream f(name.c_str());
  return f.good();
}

// Create a bankfile for a specific date
bool create_bank_file(std::string home_name, std::optional<std::string> custom_dir) {
  std::string dir;
  create_lilbank(home_name, std::nullopt);

  if (custom_dir.has_value()) {
    dir = custom_dir.value();
  } else {
    dir = "~/.local/lilbank/";
  }

  time_t now = time(0);
  tm *ltm = localtime(&now);

  std::string dir_name =
      dir +
      (std::string(std::to_string(ltm->tm_mon) + std::to_string(ltm->tm_mday)));
  if (file_exists(dir_name)) {
    return 0;
  }

  std::ofstream temp(dir_name);
  temp << "[lilbank]\n";
  return 0;
}
