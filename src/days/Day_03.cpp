#include "days/Day_03.h"
#include "core/utility.h"
#include "core/io.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

using std::string;
using std::size_t;

static io::FileOutput file("day_03.txt");

size_t day_03() {
    string banks_str = util::file_string("input/Day_03_input.txt");
    std::vector<string> banks = parse_string_to_vec(banks_str);
    size_t sum = 0;
    for (string bank : banks) {
        file.out() << "current bank: " << bank << '\n';
        sum += find_max_battery(bank);
    }
    return sum;
}

static size_t find_max_battery(const string& bank) {
    size_t idx1 = find_max_index(bank);
    size_t idx2;
    if (idx1 + 1 == bank.size()) {
        idx2 = idx1;
        idx1 = find_max_index(bank.substr(0, bank.size() - 1));
    }
    else idx2 = find_max_index(bank, idx1 + 1);

    string battery = { bank[idx1], bank[idx2] };
    file.out() << "current battery: " << battery << '\n';
    return util::str_to_num(battery);
}

static size_t find_max_index(const string& str, size_t i) {
    char max = '1';
    size_t idx = i;
    for (; i < str.size(); i++) {
        if (max < str[i]) {
            max = str[i];
            idx = i;
        }
    }
    return idx;
}

std::vector<string> parse_string_to_vec(const string& str) {
    string curr = "";
    std::vector<string> vec;
    for (char c : str) {
        if (c == '\n') {
            vec.push_back(curr);
            curr.clear();
        }
        else
            curr += c;
    }
    if (!curr.empty()) vec.push_back(curr);
    return vec;
}
