#pragma once
#include <cstddef>
#include <vector>
#include <string>

std::size_t day_03();
std::vector<std::string> parse_string_to_vec(const std::string& str);
static std::size_t find_max_battery(const std::string& bank);
static std::size_t find_max_index(const std::string& str, std::size_t i = 0);