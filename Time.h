#ifndef _TIME_H_
#define _TIME_H_

/***********************************
 * Lab task 6
 * Developed by Polina Shlepakova
 * on 04.03.2018
 * Version 1.0
 ***********************************/

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Time {
public:
	// to convert from seconds to hours
	static const double hourToDec;

	// constructor, which can be used as default
	// first parameter is seconds, so it can be used to convert seconds into Time
	Time(int s = 0, int m = 0, int h = 0);
	// copy constructor
	Time(const Time& t);
	// destructor
	~Time();

	// assignment operator
	Time& operator=(const Time& t);

	// converters
	// converter to seconds
	operator int() const;
	// converter to hours
	operator double() const;

	// selectors
	int hours() const;
	int minutes() const;
	int seconds() const;

	// modifiers
	void setHours(int h);
	void setMinutes(int m);
	void setSeconds(int s);

	// increment or decrement on 1 second
	const Time& operator++();
	const Time operator++(int);
	const Time& operator--();
	const Time operator--(int);

	static Time now();

	class BadTime {
	public:
		BadTime(const string& message, int s, int m, int h);
		const string& message() const;
		int seconds() const;
		int minutes() const;
		int hours() const;
	private:
		const string _message;
		const int _seconds;
		const int _minutes;
		const int _hours;
	};

private:
	static ofstream out;
	int _hours;
	int _minutes;
	int _seconds;

	void normalizeTime();
};

// add two time intervals
double operator+(const Time& t1, const Time& t2);
// subtract two time intervals
double operator-(const Time& t1, const Time& t2);

bool operator<(const Time& t1, const Time& t2);
bool operator>(const Time& t1, const Time& t2);
bool operator<=(const Time& t1, const Time& t2);
bool operator>=(const Time& t1, const Time& t2);

bool operator==(const Time& t1, const Time& t2);
bool operator!=(const Time& t1, const Time& t2);

// output operators
ostream& operator<<(ostream& os, const Time& t);
ostream& operator<<(ostream& os, const Time::BadTime& bt);

#endif