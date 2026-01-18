#pragma once
#include <vector>
#include <cstddef>
#include <array>
#include <iostream>

/* VecND
 - fixed size N-dimentional container
 - each row has exactly N elements array (compile time)
 - N > 0 is enforced via static_assert
 - MAX_SIZE = 1024
*/


template <typename T, std::size_t N>
class VecND {
	static_assert(N > 0, "VecND requires N > 0");
	static_assert(N <= 1024, "VecND N is too large, requires N <= 1024");

	using iterator = typename std::vector<std::array<T, N>>::iterator;
	using const_iterator = typename std::vector<std::array<T, N>>::const_iterator;

	std::vector <std::array <T, N>> data;

public:
	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	void push_back(const T& val1,const T& val2) { this->data.push_back({ val1, val2 }); }
	// will be need later as part of rule of 5
	const std::array<T, N>& at(std::size_t arr) const;
	std::array<T, N>& at(std::size_t arr);
	void erase(const_iterator it);
	void print_vec() const {
		if (begin() == end()) {
			std::cout << "<empty>\n";
			return;
		}
		for (const_iterator it = begin(); it != end(); it++) {
			const std::array<T, N>& arr = *it;
			std::cout << "[";
			for (std::size_t i = 0; i < arr.size() ; i++) {
				if (i + 1 < arr.size()) std::cout << arr[i] << ", ";
				else std::cout << arr[i] << "]\n";
			}
		}
	}
	// TODO: copy constructor, copy assignment, move constructor, move assignment op=, d'tor?, 
};

#include "VecND.tpp"