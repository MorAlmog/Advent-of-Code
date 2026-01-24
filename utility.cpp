#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "VecND.h"
#include "utility.h"

namespace util {

	bool is_odd(int num) { return num % 2; }
	bool is_even(int num) { return (num + 1) % 2; }
	int abs(int num) { return (num < 0 ? -num : num); }

	// for small integers
	// O(sqrt(n))
	bool is_prime(std::size_t n) {	
		if (n == 2 || n == 3) return true;
		if (n % 2 == 0 || n % 3 == 0) return false;
		for (std::size_t k = 1; (6*k-1) * (6*k-1) <= n; k++) {
			if ((n % (6 * k - 1) == 0) || (n % (6*k +1) == 0)) return false;
		}
		return true;
	}

	// returns factors vec with array [p_i,q_i] for num = fact p_i^q_i
	// W.C O(sqrt(n)) avg.c O(logn)
	VecND<std::size_t, 2>& factors(std::size_t num, VecND<std::size_t, 2>& factors) {
		std::size_t n = num;
		for (std::size_t p = 2; p * p <= n; p++) {
			if (n % p != 0) continue;

			std::size_t q = 0;
			do {
				q++;
				n /= p;
			} while (n % p == 0);

			factors.push_back(p, q);
		}

		if (n > 1) factors.push_back(n, 1);

		return factors;

	}

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

