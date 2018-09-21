/**********************************
 * Lab task 9
 * Developed by Polina Shlepakova
 * on 29.03.2018
 * Version 1.0
 **********************************/

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <string>
#include <iostream>
using namespace std;

// Array of elements with type Elem
template <typename Elem>
class Array {
public:
	class BadArray;

	// constructor
	explicit Array(size_t size);
	// destructor
	~Array();

	// selector-modifier of Array element
	Elem& operator[](const size_t index);
	// selector of Array element
	const Elem& operator[](const size_t index) const;

	// selector of size
	size_t size() const;

	// class to handle exceptional situations
	class BadArray {
	public:
		BadArray(const string& reason, const size_t index);
		const string& reason() const;
		size_t index() const;
		void diagnose() const;
	private:
		const string _reason;
		const size_t _index;
	};

private:
	size_t _size;
	Elem* _allocator;
	
	// forbidden
	// copy constructor
	Array(const Array<Elem>& arr);
	// assignment operator
	Array<Elem>& operator=(const Array<Elem>& arr);
};

// output operator
template <typename Elem>
ostream& operator<<(ostream& os, const Array<Elem>& arr);

/****** IMPLEMENTATIONS ******/

// constructor
template <typename Elem>
Array<Elem>::Array(size_t size): _size(size > 0 ? size : 1), _allocator(new Elem[_size]) {
	return;
}

// destructor
template <typename Elem>
Array<Elem>::~Array() { 
	delete[] _allocator;
	_allocator = 0;
}

template <typename Elem>
size_t Array<Elem>::size() const {
	return _size;
}

// selector-modifier of Array element
template <typename Elem>
Elem& Array<Elem>::operator[](const size_t index) {
	if (index >= size()) {
		throw BadArray("Bad index", index);
	}
	return _allocator[index];
}

// selector of Array element
template <typename Elem>
const Elem& Array<Elem>::operator[](const size_t index) const {
	if (index >= size()) {
		throw BadArray("Bad index", index);
	}
	return _allocator[index];
}

// output operator
template <typename Elem>
ostream& operator<<(ostream& os, const Array<Elem>& arr) {
	os << "Array of " << arr.size() << ": ";
	if (arr.size() == 0) {
		os << "empty." << endl;
	} else {
		os << arr[0];
		for (size_t i = 1; i < arr.size(); ++i) {
			os << ", " << arr[i];
		}
	}
	os << '.' << endl;
	return os;
}

/*** BadArray implementations ***/

// constructor
template <typename Elem>
Array<Elem>::BadArray::BadArray(const string& reason, const size_t index): _reason(reason), _index(index) {
	return;
}

// selectors
template <typename Elem>
const string& Array<Elem>::BadArray::reason() const {return _reason;}

template <typename Elem>
size_t Array<Elem>::BadArray::index() const {return _index;}

// show message
template <typename Elem>
void Array<Elem>::BadArray::diagnose() const {
	cerr << reason() << ": " << index() << endl;
}

#endif