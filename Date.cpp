//***********************************
// Lab task 6
// Developed by Polina Shlepakova
// on 19.02.2018
//***********************************

#include "Date.h"
#include <ctime>

ofstream Date::out("LogDate.txt");
string Date::monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
bool Date::defaultSet = false;

// initialize using default constructor
Date Date::defaultDate;

// constructors
// constructor with default parameters 
// (month defined as enum element)
Date::Date(int d, Month m, int y) {
	fillDate(d, m, y);
#ifndef NDEBUG
    out << "Date constructed: " << *this << endl;
#endif
}

// constructor with all 3 parameters
// (month defined as a number)
Date::Date(int d, int m, int y) {
	fillDate(d, Month(m), y);
#ifndef NDEBUG
    out << "Date constructed: " << *this << endl;
#endif
}

// copy constructor
Date::Date(const Date& date): 
	_day(date.day()), _month(date.month()), _year(date.year())
{
#ifndef NDEBUG
	out << "Date copied: " << *this << endl;
#endif
}

// destructor
Date::~Date() {
#ifndef NDEBUG
	out << "Date deleted: " << *this << endl;
#endif
}

// selectors
int Date::day() const {return _day;}
Date::Month Date::month() const {return Month(_month);}
int Date::year() const {return _year;}

// month in a text form
const string Date::getMonthName() const {
	return monthNames[_month - 1];
}

// modifiers
void Date::setDay(int day) {
	// use filldate to set the day
	// it will count number of days in a current month
	// and check if the input number of days is valid
	fillDate(day, month(), year());
}

void Date::setMonth(int month) {
	// use filldate to set the month
	// it will count number of days in an input month
	// and check if it is valid for current day
	fillDate(day(), Month(month), year());
}

void Date::setDYear(int year) {
	if (year < 0) {
		throw BadDate(day(), month(), year);
	} else {
		_year = year;
	}
}

// set default date using parameters
void Date::setDefault(int d, Month m, int y){
	defaultDate = Date(d, m, y);
}

// set default date using system clock
void Date::setDefault() {
	struct tm* today = new tm;
	time_t Alarm;
	time(&Alarm);
	today = gmtime(&Alarm);
	
	defaultDate._day = today -> tm_mday;
	defaultDate._month = ++(today -> tm_mon);
	defaultDate._year = today -> tm_year += 1900;
}

void Date::showDefault() {
	cout << defaultDate;
}

void Date::incDay() {
	if (day() < numberOfDays()) {
		// fits in the month
		_day++;
	} else {
		// change date to the first day of the next month
		_day = 1;
		if (month() != dec) {
			_month++;
		} else {
			// if month was december, next day will be the first day of next year
			_month = 1;
			_year++;
		}
	}
}

void Date::decDay() {
	if (day() > 1) {
		// fits in the month
		_day--;
	} else {
		if (month() != jan) {
			// will be the last day of the previous month
			_month--;
			_day = numberOfDays();
		} else {
			// if month was january, then date will be the last day of previous year
			_month = 12;
			_day = numberOfDays();
			if (year() == 1) {
				throw BadDate(day(), month(), 0);
			}
			_year--;
		}
	}
}

const Date& Date::operator++() {	
	incDay();
	return *this;
}

const Date Date::operator++(int) {
	Date prev(*this);
	incDay();
	return prev;
}

const Date& Date::operator--() {
	decDay();
	return *this;
}

const Date Date::operator--(int) {
	Date prev(*this);
	decDay();
	return prev;
}

// check if the year is a leap year
bool Date::leapYear(int y) const {
	if (y % 4 == 0) {
		if (y % 100 == 0) {
			if (y % 400 == 0) {
				return true;
            } else {
				// not divisible by 400
				return false;
			}
		} else {
			// not divisible by 100
            return true;
		}
	} else {
		// not divisible by 4
		return false;
	}
}

void Date::fillDate(int d, Month m, int y) {
	if (!defaultSet) {
		defaultSet = true;
		setDefault();
		#ifndef NDEBUG
			out << "Default date constructed" << endl;
		#endif
		return;
	}
	// if parameter is zero (default), field is initialized with value from the default date, otherwise - from parameter
	_day = d ? d : defaultDate._day;
	_month = m ? m : defaultDate._month;
	_year = y ? y : defaultDate._year;
   	
	// check the correctness of day
	if ((_day < 1) || (numberOfDays() < _day) || _year < 0) {
		throw BadDate(_day, _month, _year);
	}
};

int Date::numberOfDays(int month) const {
	if (month == 0) {
		month = _month;
	}
	switch(Month(month)) {
   		// in february check for leap year
		case feb:
			return 28 + leapYear(year());
			break;
		case apr: case jun: case sep: case nov:
			return 30;
			break;
		case jan: case mar: case may: case jul: case aug: case oct: case dec:
			return 31;
			break;
		// invalid month
		default:
			throw BadDate(_day, _month, _year);
	}
}

// returns number of days passed from 00/00/0000
Date::operator int() const {
	// initialize reult using years and days
	unsigned int res = year() * 365 + day();
 
	// add days for months in given year
	for (int i = 1; i < month() - 1; i++) {
		res += numberOfDays(i);
	}
 
	// every leap year has 366, so add 1 day for every leap year
	// current year is not considered, because if it's a leap year
	// and feb has alredy passed, 1 day was already added, while adding days for months
	int years = year() - 1;
    // year is a leap year if it is a multiple of 4,
    // multiple of 400 and not a multiple of 100
    res += years / 4 - years / 100 + years / 400;

	return res;
}

// returns the difference in days
int operator-(const Date& d1, const Date& d2) {
	return static_cast<int>(d1) - static_cast<int>(d2);
}

bool operator<(const Date& d1, const Date& d2) {
	if (d1.year() != d2.year()) {
		return d1.year() < d2.year();
	}
	if (d1.month() != d2.month()) {
		return d1.month() < d2.month();
	}
	// at this point, year and month are equal, so just compare days
	return d1.day() < d2.day();
}

bool operator>(const Date& d1, const Date& d2) {
	return d2 < d1;
}

bool operator<=(const Date& d1, const Date& d2) {
	return d1 == d2 ? true : d1 < d2;
}

bool operator>=(const Date& d1, const Date& d2) {
	return d2 <= d1;
}

bool operator==(const Date& d1, const Date& d2) {
	return	d1.year() == d2.year() && 
			d1.month() == d2.month() && 
			d1.day() == d2.day();
}

bool operator!=(const Date& d1, const Date& d2) {
	return !(d1 == d2);
}

ostream& operator<<(ostream& os, const Date& d) {
   return os << d.day() << ' ' << d.getMonthName() << ' ' << d.year();
}

ostream& operator<<(ostream& os, const Date::BadDate & bd) {
	return os << "Invalid date: day: " <<  bd._day << ", month: " << bd._month << ", year: " << bd._year << endl;
}