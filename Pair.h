#ifndef _PAIR_H_
#define _PAIR_H_

#include <iostream>
using namespace std;

/****************************************
 * TASK 7
 * A Pair contains two objects: key and value.
 * Pairs can be compared by their keys, but
 * Keys have to have operators > and == implemented for this to work
 * 
 * Developed by Polina Shlepakova
 * on 19.04.2018
 * Version 1.0
 ****************************************/
template <typename Key, typename Value>
class Pair {
public:
	// default constructor
	Pair();
	// constructor
	Pair(const Key& key, const Value& value);
	// copy constructor
	Pair(const Pair<Key, Value>& p);
	// destructor
	~Pair();
	// assignment operator
	Pair& operator=(const Pair<Key, Value>& p);

	// selectors
	const Key& key() const;
	const Value& value() const;
	// selector-modifiers
	Key& key();
	Value& value();

private:
	Key _key;
	Value _value;
	
};

// output operator
template <typename Key, typename Value>
ostream& operator<<(ostream& os, const Pair<Key, Value>& p);

// comparison operators
template <typename Key, typename Value>
bool operator==(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

template <typename Key, typename Value>
bool operator!=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

template <typename Key, typename Value>
bool operator<(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

template <typename Key, typename Value>
bool operator>(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

template <typename Key, typename Value>
bool operator<=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

template <typename Key, typename Value>
bool operator>=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2);

/*** IMPLEMENTATIONS ***/

// constructor
// will contain garbage, but otherwise impossible to create array of Pairs
template <typename Key, typename Value>
Pair<Key, Value>::Pair() {}

// constructor
template <typename Key, typename Value>
Pair<Key, Value>::Pair(const Key& key, const Value& value): 
	_key(key), _value(value) 
{}

// copy constructor
template <typename Key, typename Value>
Pair<Key, Value>::Pair(const Pair<Key, Value>& p):
	_key(p.key()), _value(p.value())
{}

// destructor
template <typename Key, typename Value>
Pair<Key, Value>::~Pair() {}

// assignment operator
template <typename Key, typename Value>
Pair<Key, Value>& Pair<Key, Value>::operator=(const Pair<Key, Value>& p) {
	key() = p.key();
	value() = p.value();
	return *this;
}

// selectors
template <typename Key, typename Value>
const Key& Pair<Key, Value>::key() const {
	return _key;
}

template <typename Key, typename Value>
const Value& Pair<Key, Value>::value() const {
	return _value;
}

// selector-modifiers
template <typename Key, typename Value>
Key& Pair<Key, Value>::key() {
	return _key;
}

template <typename Key, typename Value>
Value& Pair<Key, Value>::value() {
	return _value;
}

// output operator
template <typename Key, typename Value>
ostream& operator<<(ostream& os, const Pair<Key, Value>& p) {
	return os << "[key: " << p.key() << ", value: " << p.value() << ']';
}

/* COMPARISON OPERATORS */

template <typename Key, typename Value>
bool operator==(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return p1.key() == p2.key();
}

template <typename Key, typename Value>
bool operator!=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return !(p1 == p2);
}

template <typename Key, typename Value>
bool operator<(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return p1.key() < p2.key();
}

template <typename Key, typename Value>
bool operator>(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return p2 < p1;
}

template <typename Key, typename Value>
bool operator<=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return p1 == p2 ? true : p1 < p2;
}

template <typename Key, typename Value>
bool operator>=(const Pair<Key, Value>& p1, const Pair<Key, Value>& p2) {
	return p2 <= p1;
}

#endif