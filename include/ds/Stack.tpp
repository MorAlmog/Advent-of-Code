#include "Stack.h"

template <typename T>
Stack<T>::~Stack() { clear(); }

template <typename T>
void Stack<T>::push(const T& x) {
	head = new Node{ x, head };
	_size++;
}

template <typename T>
void Stack<T>::push(T&& x) {
	head = new Node{ std::move(x), head };
	_size++;
}

template <typename T>
T Stack<T>::pop() {
	if (!head)
		throw std::runtime_error("cannot pop from empty stack");
	T tmp_val = head->val;
	Node* tmp_node = head;
	head = head->next;
	delete tmp_node;
	_size--;
	return tmp_val;
}

template <typename T>
const T& Stack<T>::top() const {
	if (!head)
		throw std::runtime_error("cannot top from empty stack");
	return head->val;
}

template <typename T>
std::size_t Stack<T>::size() const {
	return _size;
}

template <typename T>
void Stack<T>::print(std::ostream& out) const {
	if (!head) {
		out << "stack is empty\n";
		return;
	}
	out << "stack: " << '\n';
	const Node* node = head;
	while (node) {
		out << node->val << '\n';
		node = node->next;
	}
}

template <typename T>
void Stack<T>::clear() {
	while (head) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
	_size = 0;
}

template <typename T>
bool Stack<T>::empty() const {
	return head == nullptr;
}