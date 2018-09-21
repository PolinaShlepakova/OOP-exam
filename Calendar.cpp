//***********************************
// TASK 2, 3
// Developed by Polina Shlepakova
// on 19.02.2018
//***********************************

#include "Calendar.h"
#include <ctime>
#include <cassert>

const string Calendar::weekDayNames[7] = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu",  "Fri"};
const string Calendar::holidayNames[11] = {
	"New Year", 
	"Christmas", 
	"International Women's Day", 
	"Easter", 
	"International Solidarity of Workers Day", 
	"Victory Day",  
	"Pentecost",
	"Constitution Day",
	"Independence Day",
	"Defender of the Fatherland Day",
	"Catholic Christmas"
};

// constructors
// constructs Calendar for current year
Calendar::Calendar() {
	struct tm* today = new tm;
	time_t Alarm;
	time(&Alarm);
	today = gmtime(&Alarm);
	_year = today->tm_year += 1900;
	fillHolidayDates();
}

// constructs Calendar for specified year
Calendar::Calendar(unsigned int year): _year(year) {
	fillHolidayDates();
};

// selector of year
unsigned int Calendar::year() const {return _year;}

// get day of the week
Calendar::WeekDay Calendar::weekDay(const Date& date) const {
	int monthDay = date.day();
	int month = date.month();
	int year = date.year();
	if (month == 1 || month == 2) {
		month += 12;
		year--;
	}
	int yearOfCentury = year % 100;
	int century = year / 100;
	return Calendar::WeekDay((monthDay + (13*(month + 1)) / 5 
		+ yearOfCentury + yearOfCentury / 4 + century / 4 - 2 * century) % 7);
}

// get name of the day of the week
const string& Calendar::weekDayName(const Date& date) const {
	return weekDayNames[weekDay(date)];
}

// is this date a weekend
bool Calendar::weekend(const Date& date) const {
	WeekDay day = weekDay(date);
	return day == sat || day == sun;
}

// is this date a holiday
bool Calendar::holiday(const Date& date) const {
	for (size_t i = 0; i < nHolidays; i++) {
		if (_holidayDates[i] == date) {
			return true;
		}
	}
	return false;
}

// is this day a work day (not a weekend and not a holiday)
bool Calendar::workday(const Date& date) const {
	return !weekend(date) && !holiday(date);
}

void Calendar::printHolidays() {
	for (size_t i = 0; i < nHolidays; i++) {
		cout << holidayNames[i] << ": " << _holidayDates[i] << endl;
	}
}

void Calendar::fillHolidayDates() {
	// New Year
	_holidayDates[0] = Date(1, Date::jan, year());
	// Christmas
	_holidayDates[1] = Date(7, Date::jan, year());	
	// International Women's Day 
	_holidayDates[2] = Date(8, Date::mar, year());
	// Easter 
	_holidayDates[3] = easterDate();
	// International Solidarity of Workers Day 
	_holidayDates[4] = Date(1, Date::may, year());
	// Victory Day  
	_holidayDates[5] = Date(9, Date::may, year());
	// Pentecost
	_holidayDates[6] = pentecostDate(_holidayDates[3]);
	// Constitution Day
	_holidayDates[7] = Date(28, Date::jun, year());
	// Independence Day
	_holidayDates[8] = Date(24, Date::aug, year());
	// Defender of the Fatherland Day
	_holidayDates[9] = Date(14, Date::oct, year());
	// Catholic Christmas
	_holidayDates[10] = Date(25, Date::dec, year());
}

Date Calendar::easterDate() {
	int a = (19 * (year() % 19) + 15) % 30;
	int b = (2 * (year() % 4) + 4 * (year() % 7) + 6 * a + 6) % 7;
	// old style date = 22 march + (a + b) days
	// new style date = old style + 13 days
	// new style date can start from 22 march + 13 = 4 april
	// if a + b <= (30 - 4 = 26), easter date fits in april
	// otherwise it will be in may
	if (a + b > 26) {
		return Date(a + b - 26, Date::may, year());
	}
	return Date(4 + a + b, Date::apr, year());
}

Date Calendar::pentecostDate(const Date& easterDate) {
	// pentecost date = easter date + 49 days
	int day = 49;
	int month = easterDate.month();
	assert(month == Date::apr || month == Date::may);

	// distribute 49 days
	int nDaysInMonth = month == Date::apr ? 30 : 31;
	int nDaysInNextMonth = nDaysInMonth == 30 ? 31 : 30;
	day -= (nDaysInMonth - easterDate.day());
	month++;
	if (day > nDaysInNextMonth) {
		day -= nDaysInNextMonth;
		month++;
	}

	return Date(day, month, easterDate.year());
}