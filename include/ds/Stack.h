#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iosfwd>

template <typename T>
class Stack {
	std::size_t _size = 0;
	struct Node {
		T val;
		Node* next;
	};
	Node* head = nullptr;

public:

	Stack() = default;
	~Stack();

	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;

	void push(const T& x);
	void push(T&& x);

	T pop();
	const T& top() const;

	std::size_t size() const;
	void print(std::ostream& out) const;

	bool empty() const;
	void clear();

};

#include "Stack.tpp"