#include <cstddef>
#include <string>
#include <array>
#include <cstdlib>
#include <new>
#include <exception>

#include "days/Day_03.h"
#include "days/Day_03b.h"
#include "core/io.h"
#include "core/utility.h"
#include "ds/Stack.h"
#include "constants.h"

using std::string;
using std::size_t;

static io::FileOutput file("day_03b.txt");

size_t day_03b() {
	string banks_str = util::file_string("input/Day_03_input.txt");
	std::vector<string> banks = parse_string_to_vec(banks_str);
	size_t sum = 0;
	size_t bat;
	for (string bank : banks) {
		file.out() << "current bank: " << bank << '\n';
		bat = find_max_k_battery(bank, day03b::BATTERY_NUM);
		file.out() << "max battery: " << bat << '\n';
		sum += bat;
	}

	return sum;
}

// finds the max battery for k digits battery size
static size_t find_max_k_battery(const string& bank, size_t k) {

	Stack<char> battery;
	//battery.push(bank[0]);
	//size_t i = 1;
	size_t deletions = bank.size() - k;

	for (char d : bank) {
		while (!battery.empty() && deletions > 0 && battery.top() < d) {
			battery.pop();
			deletions--;
		}
		battery.push(d);
	}

	while (deletions > 0) {
		battery.pop();
		deletions--;
	}

	string bankwards;
	bankwards.reserve(k);
	bankwards.clear();

	for (size_t i = 0; i < k; i++) {
		bankwards = battery.pop() + bankwards;
	}

	return util::str_to_num(bankwards);

}