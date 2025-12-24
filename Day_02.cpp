#include "Day_02.h"
#include "utility.h"

#include <iostream>

int main() {
	std::string rotations = util::file_string("Day_01_input.txt");
	std::vector<int> rotation_vec;

	util::parse_rotation_string(rotations, rotation_vec);
	//for (int i = 0; i < rotation_vec.size(); i++) {
	//	std::cout << rotation_vec[i] << std::endl;
	//}
	return password_calc(rotation_vec);
}

// for all n,m in N exist r<m,q in N so that n = qm+r
static int password_calc(const std::vector<int>& vec) {
	int password = 0;
	int pos = START_POS;
	for (int i = 0; i < vec.size(); i++) {
		pos += vec[i];
		int r = pos % 100;
		int q = (pos - r) / 100;
		std::cout << "pos: " << pos << " = r: " << r << ", q: " << q << std::endl;
		if (!pos) {
			password++;
		}
		pos %= 100;
		password += util::abs(q);
		std::cout << "current password: " << password << std::endl;
	}

	std::cout << password;
	
	return password;
}