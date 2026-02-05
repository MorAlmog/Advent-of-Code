#pragma once
#include <string>
#include "VecND.h"

size_t day_02();
static size_t sum_invalids_ID(std::string min, std::string max);
static size_t sum_invalids_in_range(const std::array<std::string, 2>& range);

void parse_rangeID(const std::string& str, VecND<std::string, 2>& str_range_vec);