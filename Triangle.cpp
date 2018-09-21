//*******************************************
//    TASK 1
//    Developed by Polina Shlepakova
//    on 18.04.2018
//    Version 2.0
//*******************************************

#include "Triangle.h"
#include "TriangleSegment.h"
#include <cassert>

ofstream Triangle::out("LogTriangle.txt");
unsigned int Triangle::_freeID = 0;

// constructors
// constructor by coordinates of triangle's points
Triangle::Triangle(const double x1, const double y1, 
	const double x2, const double y2,
	const double x3, const double y3):
	_myID(++_freeID), _a(x1, y1), _b(x2, y2), _c(x3, y3),
	_ab(0), _bc(0), _ca(0), 
	_ha(0), _hb(0), _hc(0),
	_haBase(0), _hbBase(0), _hcBase(0),
	_ma(0), _mb(0), _mc(0)
{
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
#ifndef NDEBUG
	out << _myID << ": triangle created " << *this << endl;
#endif
}

// constructor by triangle's points
Triangle::Triangle(const Point& a, const Point& b, const Point& c):
	_myID(++_freeID), _a(a), _b(b), _c(c),
	_ab(0), _bc(0), _ca(0), 
	_ha(0), _hb(0), _hc(0),
	_haBase(0), _hbBase(0), _hcBase(0),
	_ma(0), _mb(0), _mc(0)
{
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
#ifndef NDEBUG
	out << _myID << ": triangle created " << *this << endl;
#endif
}

// constructor by triangle's point and opposite side
Triangle::Triangle(const Point& a, const Triangle::Segment& bc):
	_myID(++_freeID), _a(a), _b(bc.start()), _c(bc.end()),
	_ab(0), _bc(0), _ca(0),
	_ha(0), _hb(0), _hc(0),
	_haBase(0), _hbBase(0), _hcBase(0),
	_ma(0), _mb(0), _mc(0)
{
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
#ifndef NDEBUG
	out << _myID << ": triangle created " << *this << endl;
#endif
}

// copy constructor
// if full is true, performs full copy (apices and sides)
Triangle::Triangle(const Triangle& t, const bool full):
	_myID(++_freeID), _a(t.apexA()), _b(t.apexB()), _c(t.apexC()),
	_ab(0), _bc(0), _ca(0),
	_ha(0), _hb(0), _hc(0),
	_haBase(0), _hbBase(0), _hcBase(0),
	_ma(0), _mb(0), _mc(0)
{
	if (full) {
		assignSegment(&Triangle::_ab, t);
		assignSegment(&Triangle::_bc, t);
		assignSegment(&Triangle::_ca, t);		
	}
#ifndef NDEBUG
	out << _myID << ": triangle copied " << *this << endl;
#endif
}

// destructor
Triangle::~Triangle() {
#ifndef NDEBUG
	out << _myID << ": triangle deleted " << *this << endl;
#endif
	deleteSegments();
}

// assignment operator (only apices)
Triangle& Triangle::operator=(const Triangle& t) {
	// copy apices
	_a = t.apexA();
	_b = t.apexB();
	_c = t.apexC();
	// delete old sides, heights and medians
	deleteSegments();
	return *this;
}

// full assignment (apices and sides)
Triangle& Triangle::assign(const Triangle& t) {
	// copy apices
	_a = t.apexA();
	_b = t.apexB();
	_c = t.apexC();
	// copy sides
	assignSegment(&Triangle::_ab, t);
	assignSegment(&Triangle::_bc, t);
	assignSegment(&Triangle::_ca, t);
	// delete old heights and medians
	deleteHeights();
	deleteMedians();
	return *this;
}

// triangle's perimeter
double Triangle::perimeter() const {
	return lengthA() + lengthB() + lengthC();
}

// triangle's area
double Triangle::area() const {
	double lenA = lengthA();
	double lenB = lengthB();
	double lenC = lengthC();
	double p = (lenA + lenB + lenC) / 2.;
	return sqrt(p * (p - lenA) * (p - lenB) * (p - lenC));
}

// selectors of apices
const Point& Triangle::apexA() const {return _a;}
const Point& Triangle::apexB() const {return _b;}
const Point& Triangle::apexC() const {return _c;}

// modifiers of apices
const Point& Triangle::setApexA(const Point& a) {
	_a = a;
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
	// delete old sides, heights and medians
	deleteSegments();
	return _a;
}

const Point& Triangle::setApexB(const Point& b) {
	_b = b;
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
	// delete old sides, heights and medians
	deleteSegments();
	return _b;
}

const Point& Triangle::setApexC(const Point& c) {
	_c = c;
	if (area() == 0) {
		throw BadTriangle("Not a triangle, area is 0", _a, _b, _c);
	}
	// delete old sides, heights and medians
	deleteSegments();
	return _c;
}

// selectors of sides
const Triangle::Segment& Triangle::sideA() const {
	if (_bc == 0) {
		_bc = new Segment(apexB(), apexC());
	}
	return *_bc;
}

const Triangle::Segment& Triangle::sideB() const {
	if (_ca == 0) {
		_ca = new Segment(apexC(), apexA());
	}
	return *_ca;
}

const Triangle::Segment& Triangle::sideC() const {
	if (_ab == 0) {
		_ab = new Segment(apexA(), apexB());
	}
	return *_ab;
}

// sides' length (using delegation)
double Triangle::lengthA() const {
	return sideA().length();
}

double Triangle::lengthB() const {
	return sideB().length();
}

double Triangle::lengthC() const {
	return sideC().length();
}

// triangle's heights
const Triangle::Segment& Triangle::heightA() const {
	if (_ha == 0) {
		_ha = new Segment(apexA(), haBase());
	}
	return *_ha;
}

const Triangle::Segment& Triangle::heightB() const {
	if (_hb == 0) {
		_hb = new Segment(apexB(), hbBase());
	}
	return *_hb;
}

const Triangle::Segment& Triangle::heightC() const {
	if (_hc == 0) {
		_hc = new Segment(apexC(), hcBase());
	}
	return *_hc;
}

// creates and returns base (end) apex of a height, which starts at startApex
Point* Triangle::heightBase(const Point& startApex,
	const Point& otherApex1, const Point& otherApex2) const
{
	double k =	( (otherApex2.y() - otherApex1.y()) * (startApex.x() - otherApex1.x()) -
				  (otherApex2.x() - otherApex1.x()) * (startApex.y() - otherApex1.y()) ) / 
				( (otherApex2.y() - otherApex1.y()) * (otherApex2.y() - otherApex1.y()) + 
				  (otherApex2.x() - otherApex1.x()) * (otherApex2.x() - otherApex1.x()) );
	
	return new Point(startApex.x() - k * (otherApex2.y() - otherApex1.y()),
				 startApex.y() + k * (otherApex2.x() - otherApex1.x()));
}

// triangle's heights' bases
const Point& Triangle::haBase() const {
	if (_haBase == 0) {
		_haBase = heightBase(apexA(), apexB(), apexC());
	}
	return *_haBase;
}

const Point& Triangle::hbBase() const {
	if (_hbBase == 0) {
		_hbBase = heightBase(apexB(), apexC(), apexA());
	}
	return *_hbBase;
}

const Point& Triangle::hcBase() const {
	if (_hcBase == 0) {
		_hcBase = heightBase(apexC(), apexA(), apexB());
	}
	return *_hcBase;
}

/*** MEDIANS ***/

// creates and returns base (end) apex of a median for specified side
Point* Triangle::medianBase(const Segment& side) const {
	return new Point((side.start().x() + side.end().x()) / 2,
					 (side.start().y() + side.end().y()) / 2);
}

// triangle's medians
const Triangle::Segment& Triangle::medianA() const {
	if (_ma == 0) {
		// median's base is saved as Segment's end Point
		_ma = new Segment(apexA(), *medianBase(sideA()));
	}
	return *_ma;
}

const Triangle::Segment& Triangle::medianB() const {
	if (_mb == 0) {
		// median's base is saved as Segment's end Point
		_mb = new Segment(apexB(), *medianBase(sideB()));
	}
	return *_mb;
}

const Triangle::Segment& Triangle::medianC() const {
	if (_mc == 0) {
		// median's base is saved as Segment's end Point
		_mc = new Segment(apexC(), *medianBase(sideC()));
	}
	return *_mc;
}

const Triangle::Segment& Triangle::median(const Segment& side) const {
	if (side == sideA()) {
		return medianA();
	} else if (side == sideB()) {
		return medianB();
	} else if (side == sideC()) {
		return medianC();
	}
	throw BadTriangle("Side doesn't exist", apexA(), apexB(), apexC());
}

// helper for copying
// copies side from t (src) to this (dest)
void Triangle::assignSegment(const Triangle::SidePtr side, const Triangle& t) {
	// src and dest are the same object
	if (this == &t) {
		return;
	}

	if ((*this).*side == 0) {
		// dest's side not assigned
		if (t.*side != 0) {
			// src's side is assigned
			// create new Segment and add it to dest
			(*this).*side = new Segment(*(t.*side));
		}
	} else {
		// dest's side is assigned
		if (t.*side == 0) {
			// src's side not assigned
			// delete dest's side
			delete((*this).*side);
		} else {
			// src's side is assigned
			// delete dest's side and assign new Segment to it
			delete((*this).*side);
			(*this).*side = new Segment(*(t.*side));
		}
	}
}

void Triangle::deleteSides() {
	delete _ab;	delete _bc;	delete _ca;
	_ab = _bc = _ca = 0;
}
void Triangle::deleteHeights() {
	delete _ha;	delete _hb;	delete _hc;
	_ha = _hb = _hc = 0;
	_haBase = _hbBase = _hcBase = 0;
}
void Triangle::deleteMedians() {
	delete _ma;	delete _mb;	delete _mc;
	_ma = _mb = _mc = 0;
}

// deletes sides, heights and medians
void Triangle::deleteSegments() {
	deleteSides();
	deleteHeights();
	deleteMedians();
}

// output operator for triangle
ostream& operator<<(ostream& os, const Triangle& t) {
	return os << t.apexA() << ", " << t.apexB() << ", " << t.apexC();
}

Triangle::BadTriangle::BadTriangle(const string message, const Point& a,
	const Point& b, const Point& c):
	_message(message), _a(a), _b(b), _c(c) 
{}

const string& Triangle::BadTriangle::message() const {return _message;}
const Point& Triangle::BadTriangle::a() const {return _a;}
const Point& Triangle::BadTriangle::b() const {return _b;}
const Point& Triangle::BadTriangle::c() const {return _c;}
