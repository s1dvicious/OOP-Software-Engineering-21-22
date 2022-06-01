#pragma once

template<typename T>
struct StackElement {

	T data;
	StackElement<T>* next;

};

template<typename T>
class Stack {

	StackElement<T>* top;

	void copyFrom(const Stack&);
	void free();

public:
	//Big Four
	Stack();
	Stack(const Stack<T>&);
	Stack& operator=(const Stack<T>&);
	~Stack();

	void push(const T&);
	void pop();
	T peek()const;
	bool isEmpty()const;
};

template<typename T>
Stack<T>::Stack() : top(nullptr) {}

template<typename T>
Stack<T>::Stack(const Stack<T>& toCopy) {

	copyFrom(toCopy);

}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& toCopy) {

	if (this != &toCopy) {

		free();
		copyFrom(toCopy);

	}

	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	free();
}


template<typename T>
void Stack<T>::push(const T& data) {

	StackElement<T>* newElement = new StackElement<T>;
	newElement->data = data;
	newElement->next = top;

	top = newElement;

}

template<typename T>
bool Stack<T>::isEmpty()const {
	return top == nullptr;
}

template<typename T>
void Stack<T>::pop() {

	if (isEmpty())
		throw "Stack is empty!";

	StackElement<T>* toDelete = top;
	top = top->next;
	delete toDelete;
	
}

template<typename T>
T Stack<T>::peek()const {

	if (isEmpty())
		throw "The stack is empty";

	return top->data;
}

template<typename T>
void Stack<T>::free() {

	StackElement<T>* toDelete;

	while (top != nullptr) {

		toDelete = top;
		top = top->next;
		delete toDelete;

	}

}

template<typename T>
void Stack<T>::copyFrom(const Stack<T>& other) {

	if (other.isEmpty()) {
		top = nullptr;
		return;
	}
	
	StackElement<T>* toCopy, * newElement, * prevElement;
	toCopy = other.top;
	newElement = new StackElement<T>;
	newElement->data = toCopy->data;
	newElement->next = nullptr;

	prevElement = newElement;
	top = newElement;
	toCopy = toCopy->next;

	while (toCopy != nullptr) {

		newElement = new StackElement<T>;
		newElement->data = toCopy->data;
		newElement->next = nullptr;

		prevElement->next = newElement;
		prevElement = newElement;
		toCopy = toCopy->next;

	}

}
