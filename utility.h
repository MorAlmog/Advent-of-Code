#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace util {

	std::string file_string(std::string file_name);
	int convert_string_to_numbers(std::string_view s_num, char sign);
	void parse_rotation_string(std::string& rotations, std::vector<int>& vec);

};

