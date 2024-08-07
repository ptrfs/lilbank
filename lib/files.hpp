#pragma once

#include <ctime>
#include <optional>
#include <string>

bool create_lilbank(std::string home_name,
                    std::optional<std::string> custom_dir);

bool file_exists(std::string name);

bool create_day_file(std::string home_name,
                     std::optional<std::string> custom_dir);
