/***********************************
 * TASK 4, 5, 6
 * Developed by Polina Shlepakova
 * on 18.04.2018
 * Version 1.0
 ***********************************/

// I wasn't allowed to use C++11 or additional libs in this course, 
// so couldn't use multithreading for this task

#include "Alarm.h"
#include <Windows.h>

const Time Alarm::cancelWaitTime = Time(7, 0, 0); // 7 seconds
const int Alarm::dayToMillis = 24 * 3600 * 1000;
const int Alarm::hourToMillis = 3600 * 1000;

// (start time in GMT)
// Alarm, which starts at specified Date on specified Time
// and is repeated if not cancelled until wait time exceeds
Alarm::Alarm(const string& message, const Date& startDate,
			const Time& startTime):
	_message(message), _startDate(startDate), 
	_startTime(startTime), _signalOn(false), _alarmOn(true)
{
	checkStart();
	sleepToSignal();	
	cout << "Signal will be repeated if the user answers 'n' and time " << cancelWaitTime << " exceeds" << endl;
	signal();
	turnOffAlarm();
}

Alarm::Alarm(const string& message, const Time& startTime):
	_message(message), _startDate(Date()), 
	_startTime(startTime), _signalOn(false), _alarmOn(true)
{
	checkStartTime();
	cout << "Signal will be repeated if the user answers 'n' and time " << cancelWaitTime << " exceeds" << endl;
	regularSignal();
}

Alarm::~Alarm() {}

// selectors
const string& Alarm::message() const {return _message;}
const Date& Alarm::startDate() const {return _startDate;}
const Time& Alarm::startTime() const {return _startTime;}
bool Alarm::signalOn() const {return _signalOn;}
bool Alarm::alarmOn() const {return _alarmOn;}

void Alarm::checkStartTime() {
	if (static_cast<double>(startTime()) >= 24.) {
		throw BadAlarm("Time doesn't exist", startDate(), startTime());
	}
}

// check start time and date
void Alarm::checkStart() {
	checkStartTime();
	Date::setDefault(); // make sure default date is today
	Date today; // initialize using default constructor
	if (startDate() < today) {
		throw BadAlarm("Alarm starts in the past", startDate(), startTime());
	}
	Time now = Time::now();
	if (startDate() == today && startTime() < now) {
		throw BadAlarm("Alarm starts in the past", startDate(), startTime());
	}
}

void Alarm::sleepToSignal() {
	Date today;
	Time now = Time::now();

	int daysToTurnOn = startDate() - today;
	double hoursToTurnOn;
	if (startTime() < now) {
		if (daysToTurnOn > 0) {
			daysToTurnOn--;
		}
		hoursToTurnOn = 24 - (now - startTime()); 
	} else {
		hoursToTurnOn = startTime() - now;
	}
	
	// sleep for 1 day at a time to avoid overflow
	for (int i = 0; i < daysToTurnOn; i++) {
		Sleep(dayToMillis);
	}
	Sleep(static_cast<DWORD>(hoursToTurnOn * hourToMillis));
	_signalOn = true;
}

//void Alarm::sleepToSignal() {
//	Sleep(static_cast<DWORD>(static_cast<double>(duration()) * hourToMillis));
//	signal();
//}

void Alarm::signal() {
	cout << "Alarm signal: " << message() << endl;
	waitToCancel();
}

void Alarm::regularSignal() {
	Calendar calendar;
	char choice = '?';
	while (alarmOn()) {
		// if it is already next year, change Calendar
		if (calendar.year() != startDate().year()) {
			calendar = Calendar();
		}
		sleepToSignal();
		if (calendar.workday(startDate())) {
			signal();
		} else {
			cout << "Not signalling today, because not a workday" << endl;
		}
		// without this option, program will have to be executed forever
		cout << "Turn off alarm (if not, will wait for the next day) (y/n)? ";
		cin >> choice;
		if (choice == 'y') {
			turnOffAlarm();
			return;
		}
		++_startDate;
		cout << "Waiting for the next day..." << endl;
	}
	return;
}

void Alarm::turnOffSignal() {
	_signalOn = false;
	cout << "Signal \"" << message() << "\" turned off" << endl;
}

void Alarm::turnOffAlarm() {
	_alarmOn = false;
	cout << "Alarm \"" << message() << "\" turned off" << endl;
}

void Alarm::waitToCancel() {
	// if this time is reached, the signal is repeated
	Time repeatTime = Time::now();
	// convert cancelWaitTime to seconds and add them to the seconds of now
	repeatTime.setSeconds(repeatTime.seconds() + static_cast<int>(cancelWaitTime));
	char choice = '?';
	while (Time::now() < repeatTime && signalOn()) {
		cout << "Cancel signal (y/n)? ";
		cin >> choice;
		if (choice == 'y') {
			turnOffSignal();
		}
	}
	if (signalOn()) {
		cout << "Repeat ";
		signal();
	}
}

ostream& operator<<(ostream& os, const Alarm& t) {
	return os << "Alarm \"" << t.message() << "\"" << endl <<
		"\tStart date: " << t.startDate() << endl <<
		"\tStart time: " << t.startTime() << endl <<
		"\tSignal turned on: " << boolalpha << t.signalOn() << endl <<
		"\tAlarm turned on: " << boolalpha << t.alarmOn() << endl;
}

Alarm::BadAlarm::BadAlarm(const string& message, const Date& startDate, const Time& startTime):
	_message(message), _startDate(startDate), _startTime(startTime) 
{}

const string& Alarm::BadAlarm::message() const {return _message;}
const Date& Alarm::BadAlarm::startDate() const {return _startDate;}
const Time& Alarm::BadAlarm::startTime() const {return _startTime;}

ostream& operator<<(ostream& os, const Alarm::BadAlarm& bt) {
	return os << bt.message() << ": " << endl <<
		"\tStart date: " << bt.startDate() << endl <<
		"\tStart time: " << bt.startTime() << endl;
}