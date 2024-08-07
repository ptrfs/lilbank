#include "files.hpp"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// App startup function to check if there is ~/.local/lilbank/, if not, create
// it
bool create_lilbank(std::string home_name,
                    std::optional<std::string> custom_dir) {
  std::string dir;

  if (custom_dir.has_value()) {
    dir = custom_dir.value();
  } else {
    dir = "/home/" + home_name + "/.local/lilbank/";
  }

  return std::filesystem::create_directory(dir);
}

// Checks if a file exists
bool file_exists(std::string name) {
  std::fstream f(name.c_str());
  return f.good();
}

// Create a dayfile for a specific date
bool create_day_file(std::string home_name,
                     std::optional<std::string> custom_dir) {
  std::string dir;
  if (create_lilbank(home_name, std::nullopt) == 1)
    return 1;

  // Making the lilbank file (it would've already been made by this time but
  // whatever)
  if (custom_dir.has_value()) {
    dir = custom_dir.value();
  } else {
    dir = "/home/" + home_name + "/.local/lilbank/day/";
  }

  // Creaing the dayfolder
  std::filesystem::create_directory(dir);

  // Initialising time
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);
  tm *ltm = localtime(&now_time_t);

  // Getting the name of the bankfile
  std::string bankfile = dir + (std::string(std::to_string(ltm->tm_mday) + "-" +
                                            std::to_string(ltm->tm_mon)) +
                                "-" + std::to_string(ltm->tm_year) + ".toml");
  if (file_exists(bankfile)) {
    return 0;
  }

  std::ofstream temp(bankfile);
  temp << "[lilbank]\n";
  return 0;
}
