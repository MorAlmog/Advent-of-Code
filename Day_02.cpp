#pragma once
#include "Day_02.h"
#include "utility.h"
#include "io.h"
#include "Vec2D.h"
#include <iostream>
#include "utility.h"

int main() {
	Vec2D<std::string> str_range_vec;
	std::string rangeID_str = util::file_string("Day_02_input.txt");
	Vec2D<int> vec;
	vec.push_back(2, 4);
	vec.push_back(1, 3);
	vec.print_vec();
	//std::cout << vec.begin()[0][0] << std::endl;


}

//void parse_rangeID(std::string& str, Vec2D<std::string> str_range_vec) {
//	auto vec_it = str_range_vec.begin();
//	for (char c : str) {
//		std::string range="";
//		switch (c) {
//			case('-'):
//				//
//
//				break;
//			case(','):
//				//
//				break;
//			default:
//				range += c;
//		}
//	}
//}



