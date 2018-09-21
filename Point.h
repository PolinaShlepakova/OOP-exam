#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <fstream>
using namespace std;

//************************************************
// Every point posesses its unique ID.
// In debug mode both constructor and destructor
// report the ID and the coordinates
// of a point created or resp. deleted
//
// Developed by Polina Shlepakova
// on 19.01.2018
// Version 1.0
//************************************************

class Point {
private:
	static ofstream out;
	static unsigned int _freeID;
	const unsigned int _myID;
	double _x;
	double _y;
public:
	Point(const double x = 0, const double y = 0);
	Point(const Point& u);
	~Point();

	double& x();
	double& y();
	const double& x() const;
	const double& y() const;
	const int getID() const;
	static int amount();

	Point& operator=(const Point& u);
	Point& operator+=(const Point& u);
};

ostream& operator<<(ostream& os, const Point& u);

const Point operator+(const Point& u, const Point& v);

bool operator==(const Point& u, const Point& v);
bool operator!=(const Point& u, const Point& v);

#endif