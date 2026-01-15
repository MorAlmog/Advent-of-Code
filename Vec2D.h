#pragma once
#include <vector>
#include <cstddef>
#include <array>
#include <iostream>



template <typename T>
class Vec2D {

	using iterator = typename std::vector<std::array<T, 2>>::iterator;
	using const_iterator = typename std::vector<std::array<T, 2>>::const_iterator;

	std::vector <std::array <T, 2 >> data;

public:
	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	void push_back(const T& val1,const T& val2) { this->data.push_back({ val1, val2 }); }
	const std::array<T, 2>& at(std::size_t r) const;
	void erase(const_iterator it);
	void print_vec() const {
		if (begin() == end()) {
			std::cout << "<empty>\n";
			return;
		}
		for (const_iterator it = begin(); it != end(); it++) {
			const std::array<T, 2>& arr = *it;
			std::cout << "[ ";
			for (std::size_t i = 0; i < arr.size() ; i++) {
				if (i + 1 < arr.size()) std::cout << arr[i] << ", ";
				else std::cout << arr[i] << " ]\n";
			}
		}
	}
};

#include "Vec2D.tpp"