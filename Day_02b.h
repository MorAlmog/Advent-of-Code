#pragma once
#include <string>
#include <set>

std::size_t day_02b();
static void invalid_ids_for_length_factor(std::string min, std::string max, std::size_t factor, std::set<size_t>& uniques);
static void invalid_ids_for_length_factors(std::string min, std::string max, std::set<size_t>& uniques);
static void invalid_ids_for_range(std::array<std::string, 2>& range, std::set<size_t>& unique_invalids);