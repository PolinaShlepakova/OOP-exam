#ifndef _DATE_H_
#define _DATE_H_

//***********************************
// Lab task 6
// Developed by Polina Shlepakova
// on 19.02.2018
//***********************************

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Date {

public:
	struct BadDate;
	// to avoid confusion between months and days
	enum Month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	
	// constructors
	// constructor with default parameters 
	// (month defined as enum element)
	Date(int d = 0, Month m = Month(0), int y = 0);
	// constructor with all 3 parameters
	// (month defined as a number)
	Date(int d, int m, int y);
	// copy constructor
	Date(const Date& date);
	~Date();

	// selectors
	int day() const;
	Month month() const;
	int year() const;

	// month in a text form
	const string getMonthName() const;

	// modifiers
	void setDay(int day);
	void setMonth(int month);
	void setDYear(int year);

	static void setDefault(int d, Month m, int y);
	static void setDefault();
	static void showDefault();

	const Date& operator++();
	const Date  operator++(int);
	const Date& operator--();
	const Date  operator--(int);

	// returns number of days passed from 00/00/0000
	operator int() const;

private:
	static ofstream out;
	int _day, _month, _year;

	bool leapYear(int y) const;
	void fillDate(int d, Month m, int y);
	int numberOfDays(int month = 0) const;
	// helper methods for inc and dec operators
	void incDay();
	void decDay();

	static string monthNames[12];
	static bool defaultSet;
	static Date defaultDate;
};

// returns the difference in days
int operator-(const Date& d1, const Date& d2);

bool operator<(const Date& d1, const Date& d2);
bool operator>(const Date& d1, const Date& d2);
bool operator<=(const Date& d1, const Date& d2);
bool operator>=(const Date& d1, const Date& d2);

bool operator==(const Date& d1, const Date& d2);
bool operator!=(const Date& d1, const Date& d2);

ostream& operator<<(ostream& os, const Date & d);

struct Date::BadDate {
	int _day, _month, _year;
	BadDate(int d, int m, int y): _day(d), _month(m), _year(y) {};
};

ostream& operator<<(ostream& os, const Date::BadDate& bd);

#endif