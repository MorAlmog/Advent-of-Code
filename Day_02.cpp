#pragma once
#include "Day_02.h"
#include "utility.h"
#include "io.h"
#include "VecND.h"
#include <iostream>

using std::size_t;
using std::string;

//static io::FileOutput file("day_02.txt");

size_t day_02() {
	VecND<string, 2> str_range_vec;

	string rangeID_str = util::file_string("Day_02_input.txt");
	parse_rangeID(rangeID_str, str_range_vec);

	size_t sum_invalids = 0;
	for (size_t i = 0; i < str_range_vec.size(); i++) {
		sum_invalids += sum_invalids_in_range(str_range_vec.at(i));
	}
	
	return sum_invalids;
}

// finds sum of invalid IDs given two strings: min_range and max_range of similar even length
static size_t sum_invalids_ID(string min, string max) {
	// TODO change to exep+throw
	if (min.size() != max.size()) return 0;
	size_t sum = 0;

	string max_prefix = max.substr(0, max.size() / 2);
	string ID_prefix = min.substr(0, min.size() / 2);

	size_t int_min = util::str_to_num(min);
	size_t int_max = util::str_to_num(max);

	size_t int_ID_prefix = util::str_to_num(ID_prefix);
	size_t int_max_prefix = util::str_to_num(max_prefix);

	size_t int_ID_invalid;
	// calculate all possible ID_prefix in range, and check if full ID is in range
	// if yes, add to sum
	while (int_ID_prefix <= int_max_prefix) {
		int_ID_invalid = util::str_to_num(ID_prefix + ID_prefix);
		if (util::belongs_in_range(int_ID_invalid, int_min, int_max)) {
			sum += int_ID_invalid;
		}
		int_ID_prefix++;
		ID_prefix = util::num_to_str(int_ID_prefix);
	}
	return sum;	
}

//static int sum_invalids_in_range(std::array<string, 2>& range) {
static size_t sum_invalids_in_range(const std::array<string, 2>& range) {
	size_t min_len = range[0].size();
	size_t max_len = range[1].size();

	size_t len = (util::is_even(min_len)) ? min_len : min_len + 1;
	if (len > max_len) return 0;	// case min_len == max_len and both odd

	size_t sum = 0;

	if (min_len == max_len) return sum_invalids_ID(range[0], range[1]);

	for (; len <= max_len; len += 2) {
		if (len == min_len) sum += sum_invalids_ID(range[0], std::string(len, '9'));
		else if (len == max_len) sum += sum_invalids_ID("1" + std::string(len - 1, '0'), range[1]);
		else sum += sum_invalids_ID("1" + std::string(len - 1, '0'), std::string(len, '9'));
	}

	return sum;
}

static void parse_rangeID(const string& str, VecND<string, 2>& str_range_vec) {
	size_t row = 0;
	bool col = false;
	string range = "";
	str_range_vec.push_back("", "");
	for (char c : str) {
		if (c == '-' || c == ',') {
			str_range_vec.at(row)[col] = range;
			range = "";
			if (col) {
				str_range_vec.push_back("", "");
				row++;
			}
			col = !col;
		}
		else {
			range += c;
		}
	}
	str_range_vec.at(row)[col] = range;
	return;
}



