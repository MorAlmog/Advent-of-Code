#include "days/Day_01b.h"
#include "days/Day_01.h"
#include "core/utility.h"
#include "core/io.h"
#include "constants.h"
#include <iostream>

int day_01b() {
	std::string rotations = util::file_string("input/Day_01_input.txt");
	std::vector<int> rotation_vec;

	parse_rotation_string(rotations, rotation_vec);
	return password_calc(rotation_vec);
}

// for all n,m in N exist r<m,q in N so that n = qm+r
static int password_calc(const std::vector<int>& vec) {
	int password = 0;
	int pos = day01::START_POS;
	//io::FileOutput day02("day_02.txt");	// test helper
	for (int i = 0; i < vec.size(); i++) {
		
		// extract abs(remainder)
		int r = vec[i] % 100;
		
		// pos > 0 if pos + r < 0 => according to intermediate value theorem pos == 0 at some point during the rotation
		// pos > 0 if pos + r > 100 => by same theorem pos == 100 at some point in the rotation
		if (pos && ((pos + r) < 0 || (pos + r) > 100))password++;
		
		// abs(remainder)
		r = (r < 0 ? r + 100 : r);
		
		// extract abs(quotient)
		int q = vec[i] / 100;
		password += util::abs(q);
		
		// calc abs(pos) under Z_100
		pos = (pos + r) % 100;
		if (!pos) password++;
	}

	return password;
}