#ifndef _PRIORITY_STACK_H_
#define _PRIORITY_STACK_H_

#include "Sequence.h"
#include "Pair.h"
#include <string>
#include <iostream>

/*******************************************
 * TASK 10
 * Developed by Polina Shlepakova
 * on 19.04.2018
 * Version 1.0
 ********************************************/
template <typename Key, typename Value>
class PriorityStack {
public:
	// constructor
	PriorityStack(): _allocator() {}
	
	// implemented in base class
	bool empty() const						{return _allocator.empty();}
	size_t size() const						{return _allocator.size();}

	// implementation depends on derived class
	const Value top() const					{return do_top();}
	void pop()								{do_pop();}
	void push(const Pair<Key, Value>& p)	{do_push(p);}

	// virtual destructor
	virtual ~PriorityStack() {};

	// to handle exceptional situations
	class BadStack {
	public:
		BadStack(const string& reason): _reason(reason) {}
		void diagnose() const			{cerr << _reason;}
	private:
		const string _reason;
	};

protected:
	Sequence<Pair<Key, Value>> _allocator;

private:
	// will be implemented in derived classes
	virtual Value do_top() const				= 0;
	virtual void do_pop()						= 0;
	virtual void do_push(const Pair<Key, Value>& p)	= 0;
};

#endif