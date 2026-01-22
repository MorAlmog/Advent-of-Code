#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "utility.h"

namespace util {

	bool is_odd(int num) { return num % 2; }
	bool is_even(int num) { return (num + 1) % 2; }
	int abs(int num) { return (num < 0 ? -num : num); }

	bool belongs_in_range(int num, int min_range, int max_range) {
		return (num >= min_range && num <= max_range);
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

	// takes a string and converts to positive integer (for now correctness of string will be assumed)
	// TODO - error proof + except throw
	std::size_t str_to_num(std::string_view s_num) {
		std::size_t num = 0;
		for (std::size_t i = 0; i < s_num.size(); i++) {
			num *= 10;
			num += s_num[i] - 48;
		}
		return num;
	}

	std::string num_to_str(std::size_t num) {
		std::size_t digit;
		std::string num_s = "";
		char digit_c;
		while (num) {
			// exstract last digit
			digit = num % 10;
			num /= 10;
			// convert to ASCII
			digit_c = digit + 48;
			num_s = digit_c + num_s;
		}
		return num_s;
	}

};

