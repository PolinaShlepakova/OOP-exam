#ifndef _Alarm_H_
#define _Alarm_H_

/***********************************
 * TASK 4, 5, 6
 * Alarm can signal at specified Date on specified Time.
 * Alarm will signal until the signal is turned off.
 * If the wait time exceeds and the signal is not turned off, 
 * the signal will be repeated.
 * 
 * Alarm can also signal regularly, every day on specified time,
 * if the day is a workday (not a weekend and not a holiday).

 * Developed by Polina Shlepakova
 * on 19.04.2018
 * Version 1.0
 ***********************************/

#include <string>
#include <iostream>
using namespace std;
#include "Date.h"
#include "Time.h"
#include "Calendar.h"

class Alarm {
public:
	// (start time in GMT)
	// Alarm, which starts at specified Date on specified Time
	// and is repeated if not cancelled until wait time exceeds
	Alarm(const string& message, const Date& startDate, 
		const Time& startTime);
	
	Alarm(const string& message, const Time& startTime);
	~Alarm();

	// selectors
	const string& message() const;
	const Date& startDate() const;
	const Time& startTime() const;
	bool signalOn() const;
	bool alarmOn() const;

	void turnOffSignal();
	void turnOffAlarm();

	class BadAlarm {
	public:
		BadAlarm(const string& message, const Date& startDate, const Time& startTime);
		const string& message() const;
		const Date& startDate() const;
		const Time& startTime() const;
	private:
		const string _message;
		const Date _startDate;
		const Time _startTime;
	};

private:
	string _message;
	Date _startDate;
	Time _startTime;
	bool _signalOn;
	bool _alarmOn;

	static const Time cancelWaitTime;
	static const int dayToMillis;
	static const int hourToMillis;

	// declared to not let the compiler gift them
	// not implemented to forbid usage
	Alarm(const Alarm& t);
	Alarm& operator=(const Alarm& t);

	// check start time and date
	void checkStart();
	void checkStartTime();
	void sleepToSignal();
	void waitToCancel();
	void signal();
	void repeat();
	void regularSignal();
};

ostream& operator<<(ostream& os, const Alarm& t);
ostream& operator<<(ostream& os, const Alarm::BadAlarm& bt);

#endif