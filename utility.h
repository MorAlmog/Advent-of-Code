#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace util {

	bool is_even(int num);
	bool is_odd(int num);
	int abs(int num);
	bool belongs_in_range(int num, int min_range, int max_range);
	void print_vec(std::vector<int>& vec);
	std::string file_string(std::string file_name);
	std::size_t str_to_num(std::string_view s_num);
	std::string num_to_str(std::size_t num);
	//void parse_rotation_string(std::string& rotations, std::vector<int>& vec);

};

