#pragma once

// #include "toml.hpp"
#include <filesystem>
#include <optional>
#include <iostream>
#include <fstream>
#include <ctime>


// App startup function to check if there is ~/.local/lilbank/, if not, create it
bool create_lilbank (std::optional <std::string> custom_dir){
  std::string dir;
  
  if (custom_dir.has_value()){
    dir = custom_dir.value();
  } else {
    dir = "~/.local/lilbank/";
  }
  if (std::filesystem::exists(dir)) return 0;

  try {
    std::filesystem::create_directory(dir);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  }
  return 0;
}

bool file_exists (std::string name){
  std::fstream f(name.c_str());
  return f.good();
}

// Create a bankfile for a specific date
bool create_bank_file (std::optional <std::string> custom_dir) {
  std::string dir;
  create_lilbank(std::nullopt);

  if (custom_dir.has_value()){
    dir = custom_dir.value();
  } else {
    dir = "~/.local/lilbank/";
  }

  time_t now = time(0);
  tm *ltm = localtime(&now);

  std::string dir_name = dir + (std::string(std::to_string(ltm->tm_mon) + std::to_string(ltm->tm_mday)));
  if (file_exists(dir_name)){
    return 0;
  }
  
  std::ofstream temp(dir_name);
  temp << "[lilbank]\n";
  return 0;
}

