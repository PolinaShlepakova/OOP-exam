/***********************************
 * Lab task 6
 * Developed by Polina Shlepakova
 * on 04.03.2018
 * Version 1.0
 ***********************************/

#include "Time.h"
#include <ctime>

ofstream Time::out("LogTime.txt");

// to convert from seconds to hours
const double Time::hourToDec = 1. / 3600.;

// constructor, which can be used as default
// first parameter is seconds, so it can be used to convert seconds into Time
Time::Time(int s, int m, int h):
	_seconds(s), _minutes(m), _hours(h) 
{
	normalizeTime();
#ifndef NDEBUG
	out << "constructed Time: " << *this << endl;
#endif
	return;
}

// copy constructor
Time::Time(const Time& t): 
	_seconds(t.seconds()), _minutes(t.minutes()), _hours(t.hours()) 
{
	// no need to normalize time, because t is already normalized
#ifndef NDEBUG
	out << "copied Time: " << *this << endl;
#endif
	return;
}

// destructor
Time::~Time() {
#ifndef NDEBUG
	out << "destructed Time: " << *this << endl;
#endif
	return;
}

// assignment operator
Time& Time::operator=(const Time& t) {
	_seconds = t.seconds();
	_minutes = t.minutes();
	_hours = t.hours();
	// no need to normalize time, because t is already normalized
	return *this;
}

// converters
// converter to seconds
Time::operator int() const {
	return hours() * 3600 + minutes() * 60 + seconds();
}

// converter to hours
Time::operator double() const {
	return static_cast<int>(*this) * hourToDec;
}

// selectors
int Time::hours() const {return _hours;}
int Time::minutes() const {return _minutes;}
int Time::seconds() const {return _seconds;}

// modifiers
void Time::setHours(int h) {
	_hours = h;
	normalizeTime();
	return;
}

void Time::setMinutes(int m) {
	_minutes = m;
	normalizeTime();
	return;
}

void Time::setSeconds(int s) {
	_seconds = s;
	normalizeTime();
	return;
}

// increment or decrement on 1 second
const Time& Time::operator++() {
	setSeconds(seconds() + 1);
	return *this;
}

const Time Time::operator++(int) {
	Time temp(*this);
	setSeconds(seconds() + 1);
	return temp;
}

const Time& Time::operator--() {
	setSeconds(seconds() - 1);
	return *this;
}

const Time Time::operator--(int) {
	Time temp(*this);
	setSeconds(seconds() - 1);
	return temp;
}

// returns current time (UTC)
Time Time::now() {
	struct tm* now;
	time_t Alarm;
	time(&Alarm);
	now = gmtime(&Alarm);
	
	return Time(now -> tm_sec, now -> tm_min, now -> tm_hour);
}

void Time::normalizeTime() {
	_minutes += seconds() / 60;
	_seconds %= 60;
	_hours += minutes() / 60;
	_minutes %= 60;

	// handle negative parameters
	if (seconds() < 0) {
		if (minutes() > 0) {
			_minutes--;
			_seconds = 60 + seconds();
		} else {
			throw BadTime("Negative time", seconds(), minutes(), hours());
		}
	}
	if (minutes() < 0) {
		if (hours() > 0) {
			_hours--;
			_minutes = 60 + minutes();
		} else {
			throw BadTime("Negative time", seconds(), minutes(), hours());
		}
	}
	if (hours() < 0) {
		throw BadTime("Negative time", seconds(), minutes(), hours());
	}
	return;
}

// add two time intervals
double operator+(const Time& t1, const Time& t2) {
	return static_cast<double>(t1) + static_cast<double>(t2);
}

// subtract two time intervals
double operator-(const Time& t1, const Time& t2) {
	return static_cast<double>(t1) - static_cast<double>(t2);
}

bool operator<(const Time& t1, const Time& t2) {
	if (t1.hours() != t2.hours()) {
		return t1.hours() < t2.hours();
	}
	if (t1.minutes() != t2.minutes()) {
		return t1.minutes() < t2.minutes();
	}
	// at this point, hours and minutes are equal, so just compare seconds
	return t1.seconds() < t2.seconds();
}

bool operator>(const Time& t1, const Time& t2) {
	return t2 < t1;
}

bool operator<=(const Time& t1, const Time& t2) {
	return t1 == t2 ? true : t1 < t2;
}

bool operator>=(const Time& t1, const Time& t2) {
	return t2 <= t1;
}

bool operator==(const Time& t1, const Time& t2) {
	return	t1.hours() == t2.hours() && 
			t1.minutes() == t2.minutes() && 
			t1.seconds() == t2.seconds();
}

bool operator!=(const Time& t1, const Time& t2) {
	return !(t1 == t2);
}

// output operator
ostream& operator<<(ostream& os, const Time& t) {
	return os << t.hours() << ':' << t.minutes() << ':' << t.seconds();
}

Time::BadTime::BadTime(const string& message, int s, int m, int h):
	_message(message), _seconds(s), _minutes(m), _hours(h) 
{}

const string& Time::BadTime::message() const {return _message;}
int Time::BadTime::seconds() const {return _seconds;}
int Time::BadTime::minutes() const {return _minutes;}
int Time::BadTime::hours() const {return _hours;}

ostream& operator<<(ostream& os, const Time::BadTime& bt) {
	return os << bt.message() << ": " <<
		bt.hours() << ':' << bt.minutes() << ':' << bt.seconds() << endl;
}