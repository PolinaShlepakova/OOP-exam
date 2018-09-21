//*******************************************
//    TASK 1
//    Developed by Polina Shlepakova
//    on 18.04.2018
//    Version 2.0
//*******************************************

#include "Triangle.h"

class Triangle::Segment {
private:
	static ofstream out;
	static unsigned int _freeID;
	const unsigned int _myID;

	// reference to triangle's apex, which is a start of the segment
	const Point& _a;
	// reference to triangle's apex or
	// a point on triangle's side (for height)
	const Point& _b;

	// declared to not let the compiler gift it
	// not implemented to forbid usage
	// assignment operator
	Segment& operator=(const Segment&);

public:
	// constructor by start and end points
	Segment(const Point& start, const Point& end);
	// copy constructor
	Segment(const Segment& s);

	// destructor
	~Segment();

	// selectors
	const Point& start() const;
	const Point& end() const;

	// length of segment
	double length() const;
	// distance from segment to point
	double distance(const Point& c) const;
};

// output operator
ostream& operator<<(ostream& os, const Triangle::Segment& s);

bool operator==(const Triangle::Segment& s1, const Triangle::Segment& s2);
bool operator!=(const Triangle::Segment& s1, const Triangle::Segment& s2);