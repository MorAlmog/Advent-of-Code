#pragma once
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <ostream>
//#include <iostream>
#include <bit>

// TODO - turn to template T
class Matrix {
	bool** _data = nullptr;
	std::size_t _rows = 0;
	std::size_t _cols = 0;
	std::size_t _capacity = 0;

public:

	// Constructors / Destructor
	Matrix() {
		_data = nullptr;
		_rows = 0;
		_cols = 0;
		_capacity = 0;
	}
	Matrix(std::size_t requested_rows, std::size_t _cols) : _cols(_cols) {
		if (_cols == 0) throw std::invalid_argument
			("matrix's cols must be set to a positive integer");

		// caculate capacity = 2^n so that 2^(n-1) < requested_rows <= 2^n
		_capacity = std::bit_ceil(requested_rows);
		// allocate space for matrix
		_data = static_cast<bool**>(std::calloc(_capacity, sizeof(*_data)));
		if (!_data) throw std::bad_alloc{};

		// allocate space for each row in requested_rows
		for (std::size_t i = 0; i < _capacity; i++) {
			bool* row = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
			if (!row) {
				_rows = i;	// allows d'tor to determine how many rows to free
				clear();
				throw std::bad_alloc{};
			}
			_data[i] = row;
		}
		_rows = requested_rows;
	}
	~Matrix() {
		clear();
		//std::cout << "matrix " << this << " is freed\n";
	}

	// Move only
	Matrix(const Matrix& rhs) = delete;
	Matrix(Matrix&& other) noexcept {
		_data = other._data;
		_rows = other._rows;
		_cols = other._cols;
		_capacity = other._capacity;
		other._data = nullptr;
		other._rows = 0;
		other._cols = 0;
		other._capacity = 0;
	}

	Matrix& operator=(const Matrix& rhs) = delete;
	Matrix& operator=(Matrix&& other) noexcept {

		if (this == &other) return *this;
		clear();

		_data = other._data;
		_rows = other._rows;
		_cols = other._cols;
		_capacity = other._capacity;
		other._data = nullptr;
		other._rows = 0;
		other._cols = 0;
		other._capacity = 0;

		return *this;
	}

	// Core methods
	void add_row() {
		if (!_cols) throw std::logic_error
			("matrix's cols must be set to a positive integer");
		if (_rows < _capacity) {
			_rows++;
			return;
		}

		// _rows == _capacity, increase capacity to 2^(n+1)
		size_t new_capacity = _capacity ? _capacity * 2 : 1;
		bool** tmp = _capacity ?
			static_cast<bool**>(std::realloc(_data, (new_capacity) * sizeof(*_data))) : 
			static_cast<bool**>(std::calloc(new_capacity, sizeof(*_data)));
		if (!tmp) throw std::bad_alloc{};
		_data = tmp;

		for (size_t i = _capacity; i < new_capacity; i++) {
			bool* row = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
			if (!row) {
				_capacity = new_capacity;
				_rows = i;
				clear();
				throw std::bad_alloc{};
			}
			tmp[i] = row;
		}
		_rows++;
		_capacity = new_capacity;
		return;
	}
	void clear(bool clear_cols = false) {
		if (!_data) {
			_rows = 0;
			if (clear_cols) _cols = 0;
			return;
		}
		for (std::size_t i = 0; i < _capacity; i++) {
			std::free(_data[i]);
		}
		std::free(_data);
		_data = nullptr;
		_rows = 0;
		_capacity = 0;
		if (clear_cols) _cols = 0;
		return;
	}
	
	void print(std::ostream& out) const {
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _cols; j++) {
				out << _data[i][j] << " ";
			}
			out << std::endl;
		}
		return;
	}
	// TODO - delete, meant for testing only
	void print_capacity(std::ostream& out) const {
		for (size_t i = 0; i < _capacity; i++) {
			for (size_t j = 0; j < _cols; j++) {
				out << _data[i][j] << " ";
			}
			out << '\n';
		}
		return;
	}

	// Getters / Setter
	std::size_t rows() const { return _rows; }
	std::size_t cols() const { return _cols; }
	std::size_t capacity() const { return _capacity; }

	void set_cols(std::size_t size) {
		if (_cols) throw std::logic_error("cols is already set");
		if (!size) throw std::logic_error("cols must be positive");
		_cols = size;
		return;
	}
};