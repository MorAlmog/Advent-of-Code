#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "utility.h"

namespace util {

	int abs(int num) {
		return (num < 0 ? -num : num);
	}

	template <typename T>
	void print_vec(const std::vector<T>& vec) {
		if (vec.empty()) std::cout << "<empty>\n";
		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << '\n';
		}
	}

	std::string file_string(std::string file_name) {

		std::ifstream file;
		file.open(file_name);

		if (file.fail()) {
			std::cout << "File failed to open" << std::endl;
			return "\0";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string file_str = buffer.str();

		file.close();

		return file_str;
	}

	//void parse_rotation_string(std::string& rotations, std::vector<int>& vec) {
	//	while (!rotations.empty()) {
	//		// R\L
	//		auto it = std::find_if(rotations.begin(), rotations.end(), [](char c) {
	//			return std::isalpha(static_cast<unsigned char>(c));
	//			});
	//		// el
	//		auto it2 = std::find_if(it, rotations.end(), [](char c) {
	//			return (c == '\n' || c == '\0');
	//			});
	//		std::size_t num = convert_string_to_numbers(std::string_view(it + 1, it2));
	//		if (*it == 'L') num *= -1;
	//		vec.push_back(num);
	//		rotations.erase(rotations.begin(), it2);
	//	}
	//}

	// takes a string and converts to positive integer (for now correctness of string will be assumed)
	// TODO - error proof + except throw
	std::size_t convert_string_to_numbers(std::string_view s_num) {
		std::size_t num = 0;
		for (int i = 0; i < s_num.size(); i++) {
			num *= 10;
			num += s_num[i] - 48;
		}
		return num;
	}

};

