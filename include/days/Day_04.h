#pragma once
#include <cstddef>
#include <string>

struct MatrixInfo {
    // TODO: convert to RAII - owning type(delete copy, add move)
    bool** data = nullptr;
    std::size_t rows = 0;
    std::size_t cols = 0;
};

std::size_t day_04();
void free_matrix(const MatrixInfo& mat);
void print_matrix(const MatrixInfo& mat, std::ostream& out = std::cout);
MatrixInfo parse_string_to_bool_matrix(const std::string& str);
std::size_t calc_cols(const std::string& str);
std::size_t calc_neighbours(const MatrixInfo& mat, std::size_t row, std::size_t col);