//*******************************************
//    TASK 1
//    Developed by Polina Shlepakova
//    on 18.04.2018
//    Version 2.0
//*******************************************

#include "TriangleSegment.h"
#include <cmath>

ofstream Triangle::Segment::out("LogSegment.txt");
unsigned int Triangle::Segment::_freeID = 0;

// constructor for segment by start and end points
Triangle::Segment::Segment(const Point& start, const Point& end):
	_myID(++_freeID), _a(start), _b(end) {
#ifndef NDEBUG
	out << _myID << ": segment created " << *this << endl;
#endif
}

// copy constructor
Triangle::Segment::Segment(const Segment& s):
_myID(++_freeID), _a(s.start()), _b(s.end())
{
#ifndef NDEBUG
	out << _myID << ": segment copied " << *this << endl;
#endif
}

// destructor for segment
Triangle::Segment::~Segment() {
#ifndef NDEBUG
	out << _myID << ": segment deleted " << *this << endl;
#endif
}

// selectors of segment's points
const Point& Triangle::Segment::start() const {return _a;}
const Point& Triangle::Segment::end() const {return _b;}

// length of segment
double Triangle::Segment::length() const {
	return sqrt((end().x() - start().x()) * (end().x() - start().x()) +
				(end().y() - start().y()) * (end().y() - start().y()));
}

// distance from segment to point
double Triangle::Segment::distance(const Point& c) const {
	// I could've used length() to compute aLen and bLen,
	// but it requires creating two extra Segment objects, so I decided against it.
	// length of the triangle's side, opposite to the point a
	double aLen = sqrt(	(c.x() - end().x()) * (c.x() - end().x()) +
						(c.y() - end().y()) * (c.y() - end().y()));
	// length of the triangle's side, opposite to the point b
	double bLen = sqrt(	(c.x() - start().x()) * (c.x() - start().x()) +
						(c.y() - start().y()) * (c.y() - start().y()));
	// length of the triangle's side, opposite to the point c
	double cLen = length();

	// triangle's half-perimeter
	double p = (aLen + bLen + cLen) / 2.;
	// triangle's area
	double s = sqrt(p * (p - aLen) * (p - bLen) * (p - cLen));
	// triangle's height
	double h = 2*s / cLen;

	// distance
	double dist;
	if ((aLen*aLen + cLen*cLen < bLen*bLen) || (bLen*bLen + cLen*cLen < aLen*aLen)) {
		// the triangle is obtuse,
		// so distance is equal to its shortest side
		dist = aLen < bLen ? aLen : bLen;
	} else {
		dist = h; // otherwise distance is equal to perpendicular (height)
	}
	return dist;
}	

// output operator for segment
ostream& operator<<(ostream& os, const Triangle::Segment& s) {
	return os << s.start() << ", " << s.end();
}

bool operator==(const Triangle::Segment& s1, const Triangle::Segment& s2) {
	// the order of points doesn't matter
	return  (s1.start() == s2.start() && s1.end() == s2.end()) ||
			(s1.start() == s2.end() && s1.end() == s2.start());
}

bool operator!=(const Triangle::Segment& s1, const Triangle::Segment& s2) {
	return !(s1 == s2);
}