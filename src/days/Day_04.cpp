#include <cstddef>
#include <string>
#include <array>
#include <exception>
#include <cstdlib>
#include <cassert>

#include "core/io.h"
#include "core/utility.h"
#include "constants.h"
#include "days/Day_04.h"

using std::string;
using std::size_t;

static io::FileOutput file("day_04.txt");

namespace {
    // a class meant for freeing matrix space safely in case of throw
    class BoolMatrixGuard {
    public: // all members are public by design

        bool** data = nullptr;
        size_t rows = 0;

        BoolMatrixGuard() = default;

        ~BoolMatrixGuard() {
            if (!data) return;
            for (size_t r = 0; r < rows; r++) {
                std::free(data[r]);
            }
            std::free(data);
        }

        BoolMatrixGuard(const BoolMatrixGuard&) = delete;
        BoolMatrixGuard& operator=(const BoolMatrixGuard&) = delete;
    };
};

std::size_t day_04() {
    string toilet_string = util::file_string("input/Day_04_input.txt");
    MatrixInfo matrix;
    try {
        matrix = parse_string_to_bool_matrix(toilet_string);
    }
    catch (const std::exception& e) {
        file.out() << e.what() << "\n";
        return 0;
    }
    //print_matrix(matrix, file.out());
    size_t sum = 0;
    for (size_t r = 0; r < matrix.rows; r++) {
        for (size_t c = 0; c < matrix.cols; c++) {
            if (matrix.data[r][c]) {
                size_t neighbours = calc_neighbours(matrix, r, c);
                if (neighbours < day04::ADJACENT_ROLL_LIMIT)
                    sum ++;
            }
        }
    }
    file.out() << "total sum: " << sum << '\n';

    free_matrix(matrix);
    return sum;
}

size_t calc_neighbours(const MatrixInfo& mat, size_t row, size_t col) {
    if (!mat.rows || !mat.cols) return 0;
    assert(("col or row out of bound", row < mat.rows && col < mat.cols));

    size_t neighbours = 0;

    size_t r_start = (row == 0) ? 0 : row - 1;
    size_t r_end = (row + 1 < mat.rows) ? row + 1 : mat.rows - 1;

    size_t c_start = (col == 0) ? 0 : col - 1;
    size_t c_end = (col + 1 < mat.cols) ? col + 1 : mat.cols - 1;

    for (size_t r = r_start; r <= r_end; r++) {
        for (size_t c = c_start; c <= c_end; c++) {
            if (r == row && c == col) continue;
            if (mat.data[r][c]) neighbours++;
        }
    }
    return neighbours;
}

MatrixInfo parse_string_to_bool_matrix(const string& str) {
    // calculate cols and include
    size_t cols = calc_cols(str);
    if (!cols) 
        throw std::invalid_argument("empty input or zero columns");
    // allocate space for bool matrix
    BoolMatrixGuard matrix;
    matrix.data = static_cast<bool**>(std::malloc(sizeof(*matrix.data)));
    if (!matrix.data) 
        throw std::bad_alloc{};

    bool* row = static_cast<bool*>(std::malloc(cols * sizeof(bool)));
    if (!row) 
        throw std::bad_alloc{};

    // initialise
    matrix.data[0] = row;
    matrix.rows = 1;
    size_t i = 0;

    // build bool matrix
    for (const char& c : str) {
        if (c == '\r') continue;
        if (c == '@' || c == '.') {
            if (i >= cols)
                throw std::runtime_error("row length exceeds allocated column count");
            row[i++] = (c == '@');
        }
        // allocate another row for matrix
        if (c == '\n') {
            if (&c == &str.back()) break;
            // allocate space for new row
            bool** tmp = static_cast<bool**>(std::realloc(matrix.data, (matrix.rows + 1) * sizeof(*matrix.data)));
            if (!tmp)
                throw std::bad_alloc{};
            matrix.data = tmp;
            row = static_cast<bool*>(std::malloc(cols * sizeof(bool)));
            if (!row)
                throw std::bad_alloc{};
            matrix.data[matrix.rows++] = row;
            i = 0;
        }
    }
    // transfer ownership:
    // insert data to struct
    MatrixInfo final_matrix{ matrix.data, matrix.rows, cols };
    // free matrix
    matrix.data = nullptr;
    matrix.rows = 0;
    return final_matrix;
}

// calculates how many columns in each row - row.size()
size_t calc_cols(const string& str) {
    if (str.empty()) return 0;
    size_t i = 0;
    while (i < str.size() && str[i] != '\n')
        i++;
    return i;
}

void free_matrix(const MatrixInfo& mat) {
    if (!mat.data) return;
    for (size_t r = 0; r < mat.rows; r++)
        std::free(mat.data[r]);
    std::free(mat.data);
    return;
}

void print_matrix(const MatrixInfo& mat, std::ostream& out) {
    if (!mat.data) return;
    out << "matrix: \n";
    for (size_t r = 0; r < mat.rows; r++) {
        for (size_t c = 0; c < mat.cols; c++) {
            out << mat.data[r][c] << " ";
        }
        out << "\n";
    }
    return;
}