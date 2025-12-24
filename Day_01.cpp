#include "Day_01.h"

using std::string;
using std::vector;

int day_01() {

	string rotations = util::file_string("Day_01_input.txt");
	vector<int> rotation_vec;

	util::parse_rotation_string(rotations, rotation_vec);
	int password = password_calc(rotation_vec);

	return password;
}

static int password_calc(const std::vector<int>& vec) {
	int pos = START_POS;
	int password = 0;
	for (int i = 0; i < vec.size(); i++) {
		pos += vec[i];
		pos %= 100;
		if (!pos) {
			password++;
		}
	}
	return password;
}