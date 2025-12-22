#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string_view>

constexpr int START_POS = 50;

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

string file_string(string file_name);
static int convert_string_to_numbers(std::string_view s_num, const char& sign);
static void parse_rotation_string(string& rotations, vector<int>& vec);
static int password_calc(const vector<int>& vec);
