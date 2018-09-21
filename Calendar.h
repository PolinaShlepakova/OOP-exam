#ifndef _CALENDAR_H_
#define _CALENDAR_H_

#include <string>
#include "Date.h"

/*******************************
 * TASK 2, 3
 * Calendar can identify weekday by date, 
 * determine whether a date is weekend, holiday or workday.
 * Developed by Polina Shlepakova
 * on 18.04.2018
 * Version 1.0
 *******************************/
class Calendar {
public:
	// to avoid confusion between different ways to number days
	enum WeekDay {sat = 0, sun, mon, tue, wed, thu, fri};

	// constructors
	// constructs Calendar for current year
	Calendar();
	// constructs Calendar for specified year
	Calendar(unsigned int year);

	// selector of year
	unsigned int year() const;

	// get day of the week
	WeekDay weekDay(const Date& date) const;
	const string& weekDayName(const Date& date) const;

	// is this date a weekend
	bool weekend(const Date& date) const;
	// is this date a holiday
	bool holiday(const Date& date) const;
	// is this day a work day (not a weekend and not a holiday)
	bool workday(const Date& date) const;

	void printHolidays();
private:
	unsigned int _year;
	static const size_t nHolidays = 11;
	Date _holidayDates[nHolidays];
	static const string weekDayNames[7];
	static const string holidayNames[nHolidays];

	void fillHolidayDates();
	Date easterDate();
	Date pentecostDate(const Date& easterDate);
};


#endif