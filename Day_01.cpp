#include "Day_01.h"
#include "utility.h"
#include "constants.h"

using std::string;
using std::vector;

int day_01() {

	string rotations = util::file_string("Day_01_input.txt");
	vector<int> rotation_vec;

	parse_rotation_string(rotations, rotation_vec);
	int password = password_calc(rotation_vec);

	return password;
}

void parse_rotation_string(std::string& rotations, std::vector<int>& vec) {
	while (!rotations.empty()) {
		// R\L
		auto it = std::find_if(rotations.begin(), rotations.end(), [](char c) {
			return std::isalpha(static_cast<unsigned char>(c));
			});
		// el
		auto it2 = std::find_if(it, rotations.end(), [](char c) {
			return (c == '\n' || c == '\0');
			});
		std::size_t num = util::str_to_num(std::string_view(it + 1, it2));
		if (*it == 'L') num *= -1;
		vec.push_back(num);
		rotations.erase(rotations.begin(), it2);
	}
	return;
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