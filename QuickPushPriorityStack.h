#ifndef _QUICK_PUSH_PRIORITY_STACK_H_
#define _QUICK_PUSH_PRIORITY_STACK_H_

#include "PriorityStack.h"

/*******************************************
 * TASK 8
 * Developed by Polina Shlepakova
 * on 19.04.2018
 * Version 1.0
 ********************************************/
template <typename Key, typename Value>
class QuickPushPriorityStack : public PriorityStack<Key, Value> {
public:	
	// constructor of empty stack
	QuickPushPriorityStack();
	// virtual destructor
	virtual ~QuickPushPriorityStack();

private:
	virtual Value do_top() const;
	virtual void do_pop();
	virtual void do_push(const Pair<Key, Value>& p);

	// seaches for the top element and returns its index
	int topIndex() const;
};

/*** IMPLEMENTATIONS ***/

// constructor of empty stack
template <typename Key, typename Value>
QuickPushPriorityStack<Key, Value>::QuickPushPriorityStack(): 
	PriorityStack() 
{}

// virtual destructor
template <typename Key, typename Value>
QuickPushPriorityStack<Key, Value>::~QuickPushPriorityStack() {}

template <typename Key, typename Value>
Value QuickPushPriorityStack<Key, Value>::do_top() const {
	return _allocator[topIndex()].value();
}

template <typename Key, typename Value>
void QuickPushPriorityStack<Key, Value>::do_pop() {
	_allocator.remove(topIndex());
}

template <typename Key, typename Value>
void QuickPushPriorityStack<Key, Value>::do_push(const Pair<Key, Value>& p) {
	_allocator.add(p);
}

// seaches for the top element and returns its index
template <typename Key, typename Value>
int QuickPushPriorityStack<Key, Value>::topIndex() const {
	if (empty()) {
		throw BadStack("Stack is empty");
	}
	// suppose the last pushed element is top element
	// save it's index
	int index = size() - 1;
	// and the element itself
	Pair<Key, Value> topPair = _allocator[index];
	// iterate downwards
	for (int i = index - 1; i >= 0; i--) {
		if (_allocator[i] < topPair) {
			// if element with higher (= smaller) priority is found, it is the new top
			// (if some element has the same priority as top, 
			// it is still not top, because it was pushed earlier)
			// save new top
			topPair = _allocator[i];
			// and it's index
			index = i;
		}
	}
	return index;
}

#endif