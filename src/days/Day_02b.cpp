#include <string>
#include <iostream>
#include <set>
#include <stdexcept>
#include <cassert>
#include "Day_02b.h"
#include "Day_02.h"
#include "utility.h"
#include "io.h"
#include "VecND.h"

using std::size_t;
using std::string;

io::FileOutput file("Day_02b_output.txt");

size_t day_02b() {
	VecND<string, 2> str_range_vec;
	string rangeID_str = util::file_string("Day_02_input.txt");
	parse_rangeID(rangeID_str, str_range_vec);

	std::set<size_t> invalid_IDs;
	for (size_t i = 0; i < str_range_vec.size(); i++)
		invalid_ids_for_range(str_range_vec.at(i), invalid_IDs);

	size_t sum = 0;
	for (auto id : invalid_IDs) 
		sum += id;
	
	file.out() << "sum of all invalid IDs: " << sum << '\n';
	return sum;
}

// calculate all invalid IDs for given range [a,b]
static void invalid_ids_for_range(std::array<string, 2>& range, std::set<size_t>& unique_invalids) {

	size_t len1 = range[0].size();
	size_t len2 = range[1].size();

	if (len1 == len2) {
		invalid_ids_for_length_factors(range[0], range[1], unique_invalids);
		return;
	}

	invalid_ids_for_length_factors(range[0], std::string(len1, '9'), unique_invalids);
	len1++;
	for (; len1 < len2 ; len1++) {
		invalid_ids_for_length_factors("1" + std::string(len1 - 1, '0'), std::string(len1, '9'), unique_invalids);
	}
	invalid_ids_for_length_factors("1" + string(len1 - 1, '0'), range[1], unique_invalids);

	return;
}

// calculate all invalid IDs in range [min, max] and add then to set uniques.
static void invalid_ids_for_length_factors(string min, string max, std::set<size_t>& uniques) {
	
	// precondition: min and max must have equal length
	assert(min.size() == max.size());
	if (min.size() != max.size())
		throw std::invalid_argument("invalid_ids_for_length_factor: min.size() != max.size()");

	size_t len = min.size();
	std::vector<size_t> factors = util::factors(len);
	// delete num (len) from factors - otherwise for factor len (repeat 1) all IDs are invalid
	auto it = std::find(factors.begin(), factors.end(), len);
	if (it != factors.end()) factors.erase(it);

	for (auto factor : factors) {
		invalid_ids_for_length_factor(min, max, factor, uniques);
	}
	return;
}

// for two strings of equal length, given a factor of len, adds unique invalid IDs to set
static void invalid_ids_for_length_factor(string min, string max, size_t factor, std::set<size_t>& uniques) {
	
	// precondition: min and max must have equal length
	assert(min.size() == max.size());
	if (min.size() != max.size())
		throw std::invalid_argument("invalid_ids_for_length_factor: min.size() != max.size()");

	size_t sum = 0;
	size_t factor2 = min.size() / factor;

	string ID_prefix = min.substr(0, factor);
	string max_prefix = max.substr(0, factor);

	size_t int_min = util::str_to_num(min);
	size_t int_max = util::str_to_num(max);

	size_t int_ID_prefix = util::str_to_num(ID_prefix);
	size_t int_max_prefix = util::str_to_num(max_prefix);

	size_t int_ID_invalid;
	string ID_invalid;
	ID_invalid.reserve(min.size());

	// calculate all possible ID_prefix in range, and check if full ID is in range
	// if yes, add to set
	while (int_ID_prefix <= int_max_prefix) {
		ID_invalid.clear();
		for (size_t i = 0; i < factor2; i++) {
			ID_invalid += ID_prefix;
		}

		if (min <= ID_invalid && ID_invalid <= max) {
			uniques.insert(util::str_to_num(ID_invalid));
			file.out() << "An invalid ID found: " << ID_invalid << '\n';
		}

		//if (util::belongs_in_range(int_ID_invalid, int_min, int_max)) {
		//	uniques.insert(int_ID_invalid);
		//	file.out() << "An invalid ID found: " << int_ID_invalid << '\n';
		//}
		int_ID_prefix++;
		ID_prefix = util::num_to_str(int_ID_prefix);
	}
	return;
}