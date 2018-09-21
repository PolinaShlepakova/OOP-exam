//**********************************
// Developed by Polina Shlepakova
// on 19.01.2018
//**********************************

#include "Point.h"

ofstream Point::out("LogPoint.txt");
unsigned int Point::_freeID = 0;

Point::Point(const double x, const double y): _myID(++_freeID), _x(x), _y(y) {
#ifndef NDEBUG
	out << _myID << ": point created " << *this << endl;
#endif
}

Point::Point(const Point& u): _myID(++_freeID), _x(u._x), _y(u._y) {
#ifndef NDEBUG
	out << _myID << ": point copied " << *this << endl;
#endif
}

Point::~Point() {
#ifndef NDEBUG
	out << _myID << ": point deleted " << *this << endl;
#endif
}

// selector-modifiers
double& Point::x() {return _x;}
double& Point::y() {return _y;}

// selectors
const double& Point::x() const {return _x;}
const double& Point::y() const {return _y;}

const int Point::getID() const {return _myID;}

int Point::amount() {return _freeID;}

Point& Point::operator=(const Point& u) {
	_x = u._x;
	_y = u._y;
	return *this;
}

Point& Point::operator+=(const Point& u) {
	_x += u._x;
	_y += u._y;
	return *this;
}

ostream& operator<<(ostream& os, const Point& u) {
	os << '(' << u.x() << ", " << u.y() << ')';
	return os;
}
 
const Point operator+(const Point& u, const Point& v) {
	return Point(u.x() + v.x(), u.y() + v.y());
}

bool operator==(const Point& u, const Point& v) {
	return (u.x() == v.x()) && (u.y() == v.y());
}

bool operator!=(const Point& u, const Point& v) {
	return !(u == v);
}