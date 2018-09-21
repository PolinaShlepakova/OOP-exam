/**********************************
 * TASK 8, 9
 * Sequence stores a sequence of Elems.
 * Allows to add element to the end of the sequence,
 * insert element on the specified position.
 * Developed by Polina Shlepakova
 * on 07.04.2018
 * Version 1.0
 **********************************/

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "Array.h"
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

// Sequence of elements of type Elem
template <typename Elem>
class Sequence {
public:
	class BadSeq;

	// constructor, which forbids implicit conversions
	explicit Sequence(size_t capacity = 10);
	// destructor
	~Sequence();

	// how many elements can fit it in a container
	size_t capacity() const;
	// how many elements are currently in a container
	size_t size() const;
	// is sequence empty (has 0 elements)?
	bool empty() const;
	// is sequence full (size == capacity)?
	bool full() const;

	// make sequence empty
	Sequence<Elem>& clear();

	// selector of element
	const Elem& operator[](size_t index) const;
	// selector-modifier of element
	Elem& operator[](size_t index);

	// add to the end of the sequence
	Sequence<Elem>& add(const Elem& elem);
	// insert element on specified index 
	Sequence<Elem>& insert(const Elem& elem, size_t index);
	// shorten a sequence by one element
	Sequence<Elem>& cut();
	// remove element with specified index
	Sequence<Elem>& remove(size_t index);
	// checks whether Sequence contains elem
	bool contains(const Elem& elem) const;

	// class to handle exceptional situations
	class BadSeq {
	public:
		BadSeq(const string& reason);
		const string& reason() const;
		void diagnose() const;
	private:
		const string _reason;
	};

private:
	// number of elements currently in the sequence
	size_t _size;
	Array<Elem>* _allocator;

	// resizes _allocator to newSize
	void resize(size_t newSize);
	// check if element with such index exists
	void checkIndex(size_t index) const;

	Sequence<Elem>& doInsert(Elem elem, size_t index);
	Sequence<Elem>& doRemove(size_t index);

	// forbidden
	Sequence(const Sequence<Elem>&);
	Sequence<Elem>& operator=(const Sequence<Elem>&);
};

// output operator
template <typename Elem>
ostream& operator<<(ostream& os, const Sequence<Elem>& seq);


/*** IMPLEMENTATIONS ***/

// constructor, which forbids implicit conversions
template <typename Elem>
Sequence<Elem>::Sequence(size_t capacity): _size(0), _allocator(new Array<Elem>(capacity)) {
	return;
}

// destructor
template <typename Elem>
Sequence<Elem>::~Sequence() {
	delete _allocator;
	_allocator = 0;
	return;
}

// how many elements can fit it in a container
template <typename Elem>
size_t Sequence<Elem>::capacity() const {
	return _allocator->size();
}

// how many elements are currently in a container
template <typename Elem>
size_t Sequence<Elem>::size() const {
	return _size;
}

// is sequence empty (has 0 elements)?
template <typename Elem>
bool Sequence<Elem>::empty() const {
	return size() == 0;
}

// is sequence full (size == capacity)?
template <typename Elem>
bool Sequence<Elem>::full() const {
	return size() == capacity();
}

// make sequence empty
template <typename Elem>
Sequence<Elem>& Sequence<Elem>::clear() {
	_size = 0;
	return *this;
}

// selector of element
template <typename Elem>
const Elem& Sequence<Elem>::operator[](size_t index) const {
	checkIndex(index);
	return _allocator->operator[](index);
}

// selector-modifier of element
template <typename Elem>
Elem& Sequence<Elem>::operator[](size_t index) {
	checkIndex(index);
	return _allocator->operator[](index);
}

// add to the end of the sequence
template <typename Elem>
Sequence<Elem>& Sequence<Elem>::add(const Elem& elem) {
	return doInsert(elem, size());
}

// insert element on specified index 
template <typename Elem>
Sequence<Elem>& Sequence<Elem>::insert(const Elem& elem, size_t index) {
	if (index > size()) {
		throw BadSeq("Previous element does not exist");
	}
	return doInsert(elem, index);
}

// shorten a sequence by one element
template <typename Elem>
Sequence<Elem>& Sequence<Elem>::cut() {
	if (empty()) {
		throw BadSeq("Sequence is empty");
	}
	return doRemove(size() - 1);
}

// remove element with specified index
template <typename Elem>
Sequence<Elem>& Sequence<Elem>::remove(size_t index) {
	checkIndex(index);
	return doRemove(index);
}

// checks whether Sequence contains elem
template <typename Elem>
bool Sequence<Elem>::contains(const Elem& elem) const {
	for (size_t i = 0; i < size(); ++i) {
		if ((*this)[i] == elem) {
			return true;
		}
	}
	return false;
}

/* PRIVATE METHODS */

// resizes _allocator to newSize
template <typename Elem>
void Sequence<Elem>::resize(size_t newSize) {
	// create new allocator of required size
	Array<Elem>* newAllocator = new Array<Elem>(newSize);
	// iterate over both arrays until one of them ends
	for (size_t i = 0; i < size() && i < newSize; ++i) {
		// copy elements from this sequence to newAllocator
		(*newAllocator)[i] = (*this)[i];
	}
	delete _allocator;
	_allocator = newAllocator;
	return;
}

// check if element with such index exists
template <typename Elem>
void Sequence<Elem>::checkIndex(size_t index) const {
	if (empty()) {
		throw BadSeq("Sequence is empty");
	}
	if (index >= size()) {
		throw BadSeq("Element with this index doesn't exist");
	}
}

template <typename Elem>
Sequence<Elem>& Sequence<Elem>::doInsert(Elem elem, size_t index) {
	// interface methods should call this method using only correct index
	// so use assert instead of exception
	assert(index <= size());
	// resize if needed
	if (full()) {
		resize(capacity() * 2);
	}
	++_size;
	// move elements on the right of index one position to the right
	for (size_t i = size() - 1; i > index; --i) {
		(*this)[i] = (*this)[i - 1];
	}
	// insert new element
	(*this)[index] = elem;
	return *this;  
}

template <typename Elem>
Sequence<Elem>& Sequence<Elem>::doRemove(size_t index) {
	// interface methods should call this method using only correct index
	// so use assert instead of exception
	assert(index < size());
	// resize if needed
	if (size() <= (capacity() / 4)) {
		resize(capacity() / 2);
	}
	// move elements on the right of index one position to the left
	for (size_t i = index; i < size() - 1; ++i) {
		(*this)[i] = (*this)[i + 1];
	}
	--_size;
	return *this;
}

/* UTILITIES */

// output operator
template <typename Elem>
ostream& operator<<(ostream& os, const Sequence<Elem>& seq) {
	os << "Sequence of " << seq.size() << ": ";
	if (seq.empty()) {
		os << "empty";
	} else {
		os << seq[0];
		for (size_t i = 1; i < seq.size(); ++i) {
			os << ", " << seq[i];
		}
	}
	os << '.';
	return os;
}

/*** BadSeq implementations ***/

// constructor
template <typename Elem>
Sequence<Elem>::BadSeq::BadSeq(const string& reason): _reason(reason) {
	return;
}

// selector
template <typename Elem>
const string& Sequence<Elem>::BadSeq::reason() const {return _reason;}

// show message
template <typename Elem>
void Sequence<Elem>::BadSeq::diagnose() const {
	cerr << reason() << endl;
}

#endif