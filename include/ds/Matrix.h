#pragma once
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

// will later become template T
class Matrix {
	bool** _data;
	std::size_t _rows;
	std::size_t _cols;

public:

	Matrix() {
		_data = nullptr;
		_rows = 0;
		_cols = 0;
	}

	Matrix(std::size_t requested_rows, std::size_t _cols) : _cols(_cols) {
		_rows = 0;
		if (_cols == 0) throw std::invalid_argument
			("matrix's cols must be set to a positive integer");
		_data = static_cast<bool**>(std::calloc(requested_rows, sizeof(*_data)));
		if (!_data) throw std::bad_alloc{};
		for (std::size_t i = 0; i < requested_rows; i++) {
			bool* row = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
			if (!row) {
				clear();
				throw std::bad_alloc{};
			}
			_data[i] = row;
			_rows++;
		}
	}

	~Matrix() {
		clear();
	}

	Matrix(const Matrix& rhs) = delete;
	Matrix(Matrix&& other) noexcept {
		_data = other._data;
		_rows = other._rows;
		_cols = other._cols;
		other._data = nullptr;
		other._rows = 0;
		other._cols = 0;
	}

	Matrix& operator=(const Matrix& rhs) = delete;
	Matrix& operator=(Matrix&& other) noexcept {

		if (this == &other) return *this;
		clear();

		_data = other._data;
		_rows = other._rows;
		_cols = other._cols;
		other._data = nullptr;
		other._rows = 0;
		other._cols = 0;

		return *this;
	}

	void add_row() {
		if (!_cols) throw std::logic_error
			("matrix's cols must be set to a positive integer");
		bool** tmp = static_cast<bool**>(std::realloc(_data, (_rows + 1) * sizeof(*_data)));
		_data = tmp;
		if (!data) throw std::bad_alloc{};
		bool* row = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
		if (!row) throw std::bad_alloc{};
		_data[_rows++] = row;
		return;
	}

	void clear() {
		if (!_data) {
			_cols = 0;
			_rows = 0;
			return;
		}
		for (std::size_t i = 0; i < _rows; i++) {
			std::free(_data[i]);
		}
		std::free(_data);
		_data = nullptr;
		_rows = 0;
		_cols = 0;
		return;
	}

	// getters
	bool** data() const {
		return _data;
	}
	std::size_t rows() const {
		return _rows;
	}
	std::size_t cols() const {
		return _cols;
	}

	// setter
	void set_cols(std::size_t size) {
		if (!size) throw std::logic_error("cols must be positive");
		if (_cols) throw std::logic_error("cols is already set");
		_cols = size;
		return;
	}
};