#ifndef _QUICK_TOP_PRIORITY_STACK_H_
#define _QUICK_TOP_PRIORITY_STACK_H_

#include "PriorityStack.h"

/*******************************************
 * TASK 9
 * Developed by Polina Shlepakova
 * on 19.04.2018
 * Version 1.0
 ********************************************/
template <typename Key, typename Value>
class QuickTopPriorityStack : public PriorityStack<Key, Value> {
public:	
	// constructor of empty stack
	QuickTopPriorityStack();
	// virtual destructor
	virtual ~QuickTopPriorityStack();

private:
	virtual Value do_top() const;
	virtual void do_pop();
	virtual void do_push(const Pair<Key, Value>& p);

	// seaches for the index where to insert pair
	int insertIndex(const Pair<Key, Value>& pair) const;
};

/*** IMPLEMENTATIONS ***/

// constructor of empty stack
template <typename Key, typename Value>
QuickTopPriorityStack<Key, Value>::QuickTopPriorityStack(): 
	PriorityStack() 
{}

// virtual destructor
template <typename Key, typename Value>
QuickTopPriorityStack<Key, Value>::~QuickTopPriorityStack() {}

template <typename Key, typename Value>
Value QuickTopPriorityStack<Key, Value>::do_top() const {
	if (empty()) {
		throw BadStack("Stack is empty");
	}
	return _allocator[size() - 1].value();
}

template <typename Key, typename Value>
void QuickTopPriorityStack<Key, Value>::do_pop() {
	if (empty()) {
		throw BadStack("Stack is empty");
	}
	_allocator.cut();
}

template <typename Key, typename Value>
void QuickTopPriorityStack<Key, Value>::do_push(const Pair<Key, Value>& p) {
	_allocator.insert(p, insertIndex(p));
}

// seaches for the index where to insert pair
template <typename Key, typename Value>
int QuickTopPriorityStack<Key, Value>::insertIndex(const Pair<Key, Value>& pair) const {
	int index = size() - 1;
	// iterate downwards
	while (index >= 0 && _allocator[index] < pair) {
		// the first element with lower or equal (= bigger or equal) 
		// priority is the element, on top of which pair has to be placed
		// so index = index of found element + 1
		index--;
	}
	return index + 1;
}

#endif