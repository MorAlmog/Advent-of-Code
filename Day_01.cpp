#include "Day_01.h"

int main() {

	string rotations = file_string("Day_01_input.txt");
	string curr_rot;
	vector<int> rotation_vec;

	parse_rotation_string(rotations, rotation_vec);
	int password = password_calc(rotation_vec);

	cout << "password: " << password << endl;

	return 0;
}

void parse_rotation_string(string& rotations, vector<int>& vec) {
	while (!rotations.empty()) {
		// R\L
		auto it = std::find_if(rotations.begin(), rotations.end(), [](char c) {
			return std::isalpha(static_cast<unsigned char>(c));
			});
		// el
		auto it2 = std::find_if(it, rotations.end(), [](char c) {
			return (c == '\n' || c == '\0');
			});

		vec.push_back(convert_string_to_numbers(std::string_view(it + 1, it2), *it));
		rotations.erase(rotations.begin(), it2);
	}

}

static int password_calc(const vector<int>& vec) {
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

static int convert_string_to_numbers(std::string_view s_num, const char& sign) {
	int num = 0;
	char num_c = '~';
	for (int i = 0; i < s_num.size(); i++) {
		num *= 10;
		num += s_num[i] - 48;
	}
	if (sign == 'L') {
		num *= -1;
	}
	// for all n in Z_n : if a=qn+r then [a]_n = [r]_n 
	num = num % 100;
	return num;
}

string file_string(string file_name) {

	std::ifstream file;
	file.open(file_name);

	if (file.fail()) {
		cout << "File failed to open" << endl;
		return "\0";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	string file_str = buffer.str();


	file.close();

	return file_str;
}