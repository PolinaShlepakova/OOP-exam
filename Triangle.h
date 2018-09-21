#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>
#include <fstream>
using namespace std;
#include "Point.h"
#include <string>
class Point;

//*******************************************
// TASK 1
// Triangle's apices are its components.
// Sides, heights, heights' bases and medians are pointers, 
// initialized as zeroes and created on demand (aggregation by pointers).
// Sides have points, which are references to the triangle's apices 
// (aggregation by references).
// This way, every object a triangle contains,
// is contained inside it only once,
// which makes it the most effective representation of triangle.
//
// Developed by Polina Shlepakova
// on 18.04.2018
// Version 2.0
//*******************************************
class Triangle {
public:
	// built-in class
	class Segment;
	typedef Segment* Triangle::* SidePtr;

	// constructors
	// constructor by coordinates of triangle's points
	Triangle(const double x1 = 0, const double y1 = 0, 
		const double x2 = 1, const double y2 = 0,
		const double x3 = 0, const double y3 = 1);
	// constructor by triangle's points
	Triangle(const Point& a, const Point& b, const Point& c);
	// constructor by triangle's point and opposite side
	Triangle(const Point& a, const Segment& bc);
	// copy constructor
	Triangle (const Triangle& t, const bool full = false);

	// destructor
	~Triangle();

	// assignment operator
	Triangle& operator=(const Triangle& t);
	// full assignment (apices and sides)
	Triangle& assign(const Triangle& t);

	// triangle's perimeter
	double perimeter() const;
	// triangle's area
	double area() const;

	// selectors of apices
	const Point& apexA() const;
	const Point& apexB() const;
	const Point& apexC() const;

	// modifiers of apices
	const Point& setApexA(const Point& a);
	const Point& setApexB(const Point& b);
	const Point& setApexC(const Point& c);

	// selectors of sides (if not assigned, are created)
	const Segment& sideA() const;
	const Segment& sideB() const;
	const Segment& sideC() const;

	// sides' length (using delegation)
	double lengthA() const;
	double lengthB() const;
	double lengthC() const;

	// triangle's heights
	const Segment& heightA() const;
	const Segment& heightB() const;
	const Segment& heightC() const;

	// triangle's medians for every side
	const Segment& medianA() const;
	const Segment& medianB() const;
	const Segment& medianC() const;
	// triangle's median for specified side
	const Segment& median(const Segment& side) const;

	class BadTriangle {
	public:
		BadTriangle(const string message, const Point& a,
			const Point& b, const Point& c);
		const string& message() const;
		const Point& a() const;
		const Point& b() const;
		const Point& c() const;
	private:
		const string _message;
		const Point& _a;
		const Point& _b;
		const Point& _c;
	};

private:
	static ofstream out;
	static unsigned int _freeID;
	const unsigned int _myID;

	// triangle's apices (points)
	Point _a, _b, _c;
	// triangle's sides (segments)
	mutable Segment *_ab, *_bc, *_ca;

	// triangle's heights
	mutable Segment *_ha, *_hb, *_hc;
	// triangle's heights' bases
	mutable Point *_haBase, *_hbBase, *_hcBase;

	// triangle's medians
	mutable Segment *_ma, *_mb, *_mc;

	// creates and returns base (end) apex of a height, which starts at startApex
	Point* Triangle::heightBase(const Point& startApex,
		const Point& otherApex1, const Point& otherApex2) const;
	// creates and returns base (end) apex of a median for specified side
	Point* Triangle::medianBase(const Segment& side) const;

	// triangle's heights' bases
	const Point& haBase() const;
	const Point& hbBase() const;
	const Point& hcBase() const;

	// helper for copying
	void assignSegment(const SidePtr side, const Triangle& t);
	
	void deleteSides();
	void deleteHeights();
	void deleteMedians();
	// deletes sides, heights and medians
	void deleteSegments();
};

// output operator
ostream& operator<<(ostream& os, const Triangle& t);

#endif