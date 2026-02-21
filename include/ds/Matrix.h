#pragma once
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <ostream>
#include <bit>
#include <limits>
#include <string>

// TODO - turn to template T
class Matrix {
	bool** _data = nullptr;
	std::size_t _rows = 0;
	std::size_t _cols = 0;
	std::size_t _capacity = 0;

public:


	// Constructors / Destructor
	Matrix() = default;
	Matrix(std::size_t requested_rows, std::size_t cols) : _cols(cols) {
		if (_cols == 0) throw std::invalid_argument
			("matrix's cols must be set to a positive integer");

		// caculate capacity = 2^n so that 2^(n-1) < requested_rows <= 2^n
		_capacity = std::bit_ceil(requested_rows);

		// overflow check
		if (_capacity > std::numeric_limits<std::size_t>::max() / sizeof(*_data))
			throw std::length_error("matrix too large (pointer array overflow)");

		if (_cols > std::numeric_limits<std::size_t>::max() / sizeof(bool))
			throw std::length_error("matrix too large (row overflow)");

		// allocate space for matrix
		_data = static_cast<bool**>(std::calloc(_capacity, sizeof(*_data)));
		if (!_data)
			throw std::bad_alloc{};

		// allocate space for each row in _capacity
		for (std::size_t i = 0; i < requested_rows; i++) {
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
		// TODO - when adding logger, comment *this is freed
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

		// allocation check
		if (_cols > std::numeric_limits<std::size_t>::max() / sizeof(bool))
			throw std::length_error("matrix too large (row overflow)");

		if (_rows < _capacity) {
			_data[_rows] = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
			if (!_data[_rows]) throw std::bad_alloc{};
			_rows++;
			return;
		}

		// allocation check
		std::size_t old_capacity = _capacity;
		if (old_capacity > std::numeric_limits<std::size_t>::max() / 2)
			throw std::length_error("matrix capacity overflow");
		// _rows == _capacity, increase capacity to 2^(n+1)
		std::size_t new_capacity = old_capacity ? old_capacity * 2 : 1;
		if (new_capacity > std::numeric_limits<std::size_t>::max() / sizeof(*_data))
			throw std::length_error("allocation size overflow");

		bool** new_data = static_cast<bool**>(std::calloc(new_capacity, sizeof(*_data)));
		if (!new_data) throw std::bad_alloc{};

		for (std::size_t i = 0; i < _rows; i++) {
			new_data[i] = _data[i];
		}

		//std::size_t i = old_capacity;

		new_data[old_capacity] = static_cast<bool*>(std::calloc(_cols, sizeof(bool)));
		if (!new_data[old_capacity]) {
			std::free(new_data);
			throw std::bad_alloc{};
		}

		std::free(_data);
		_data = new_data;
		_capacity = new_capacity;
		_rows++;
		return;
	}

	void clear(bool clear_cols = false) {
		if (!_data) {
			_rows = 0;
			if (clear_cols) _cols = 0;
			return;
		}
		for (std::size_t i = 0; i < _rows; i++) {
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
		for (std::size_t i = 0; i < _rows; i++) {
			for (std::size_t j = 0; j < _cols; j++) {
				out << _data[i][j] << " ";
			}
			out << '\n';
		}
		return;
	}

	// 2D Access
	class Row {
		bool* _row_ptr;
		std::size_t _row_cols;
	public:
		Row(bool* row_ptr, std::size_t cols) : _row_ptr(row_ptr), _row_cols(cols) {}
		bool& operator[](std::size_t col) {
			if (col >= _row_cols) 
				throw std::out_of_range("column index is out of range");
			return _row_ptr[col];
		}
		const bool& operator[](std::size_t col) const {
			if (col >= _row_cols)
				throw std::out_of_range("column index is out of range");
			return _row_ptr[col];
		}
	};

	Row operator[](std::size_t row) {
		if (row >= _rows)
			throw std::out_of_range("row index is out of range");
		return Row(_data[row], _cols);
	}
	Row operator[](std::size_t row) const {
		if (row >= _rows)
			throw std::out_of_range("row index is out of range");
		return Row(_data[row], _cols);
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