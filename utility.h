#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace util {

	int abs(int num);
	void print_vec(std::vector<int>& vec);
	std::string file_string(std::string file_name);
	std::size_t convert_string_to_numbers(std::string_view s_num);
	//void parse_rotation_string(std::string& rotations, std::vector<int>& vec);

};

