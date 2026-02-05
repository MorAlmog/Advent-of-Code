#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <iostream>	// when moving print_vec to template delete this

template <typename T, std::size_t N>
class VecND;

namespace util {

	// math functions

	// basic
	bool is_even(int num);
	bool is_odd(int num);
	int abs(int num);

	// Core overload: exponent is size_t
	template <typename T>
	requires (std::integral<T> || std::floating_point<T>)
	std::size_t ipow(T base, size_t exp) {
		if (exp == 0) return T{ 1 };		// by convention, including 0^0
		std::size_t res = pow(base, exp / 2);
		if (is_even(exp)) return res * res;
		else return base * res * res;
	}

	// Convenience overload: any integral exponent, runtime-check negatives
	template <typename T, std::integral E>
	requires (std::integral<T> || std::floating_point<T>)
	T ipow(T base, E exp) {
		if constexpr (std::is_signed_v<E>) {
			if (exp < 0) {
				throw std::invalid_argument("ipow: negative exponent");
			}
		}
		return ipow(base, static_cast<std::size_t>(exp));
	}

	// others
	bool is_prime(std::size_t num);
	VecND<std::size_t, 2> prime_factors(std::size_t num);
	std::vector<std::size_t> factors(std::size_t num);

	// helpers
	bool belongs_in_range(int num, int min_range, int max_range);
	//void print_vec(std::vector<int>& vec);
	template <typename T>
	void print_vec(const std::vector<T>& vec, std::ostream& out = std::cout) {
		if (vec.empty()) out << "<empty>\n";
		for (int i = 0; i < vec.size(); i++) {
			out << vec[i] << '\n';
		}
	}
	std::string file_string(std::string file_name);
	std::size_t str_to_num(std::string_view s_num);
	std::string num_to_str(std::size_t num);
};

