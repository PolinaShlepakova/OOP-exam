//*******************************************
// Developed by Polina Shlepakova
// on 19.04.2018
// Version 1.0
//*******************************************

#include "Triangle.h"
#include "TriangleSegment.h"
#include "Date.h"
#include "Calendar.h"
#include "Alarm.h"
#include "Time.h"
#include "Pair.h"
#include "PriorityStack.h"
#include "QuickPushPriorityStack.h"
#include "QuickTopPriorityStack.h"

#include <string>
#include <iostream>
using namespace std;

void testFullTriangle();
void testMedians();
void testWeekDays();
void testHolidays();
void testAlarm();
void testRegularAlarm();
void testPair();
void testStack(PriorityStack<int, string>& stack);

int main() {
	cout << "\n============ TASK 1 ============\n" << endl;
	//testFullTriangle();
	testMedians();

	cout << "\n============ TASK 2 ============\n" << endl;	
	testWeekDays();

	cout << "\n============ TASK 3 ============\n" << endl;
	testHolidays();

	cout << "\n============ TASK 4 and 5 ============\n" << endl;
	testAlarm();

	cout << "\n============ TASK 6 ============\n" << endl;
	testRegularAlarm();

	cout << "\n============ TASK 7 ============\n" << endl;
	testPair();

	cout << "\n============ TASK 8 and 10 ============\n" << endl;
	QuickPushPriorityStack<int, string> quickPush;
	testStack(quickPush);

	cout << "\n============ TASK 9 and 10 ============\n" << endl;
	QuickTopPriorityStack<int, string> quickTop;
	testStack(quickTop);

	return 0;
}

void testFullTriangle() {
	try {
		// constructors
		const Triangle t0; // default
		Triangle t1(-3, 0, 0, 0, -5, 2); // by coordinates
		Point a;
		Point b(1, 1);
		Point c(-1, 1);
		Triangle t2(a, b, c); // by points			
		Point d(-4, 0);
		Point e(5, 5);
		Point f(5, -5);
		Triangle::Segment dSide(e, f);
		Triangle t3(d, dSide); // by point and opposite side

		cout << "\n====== SELECTORS OF APICES ======" << endl;
		cout << "t0: " << t0 << endl;
		cout << "t0.apexA() = " << t0.apexA() << endl;
		cout << "t0.apexB() = " << t0.apexB() << endl;
		cout << "t0.apexC() = " << t0.apexC() << endl;
		cout << "t1: " << t1 << endl;
		cout << "t1.apexA() = " << t1.apexA() << endl;
		cout << "t1.apexB() = " << t1.apexB() << endl;
		cout << "t1.apexC() = " << t1.apexC() << endl;

		cout << "\n====== SIDES ======" << endl;
		cout << "t0: " << t0 << endl;
		cout << "t0.sideA() = " << t0.sideA() << endl;
		cout << "t0.sideB() = " << t0.sideB() << endl;
		cout << "t0.sideC() = " << t0.sideC() << endl;
		cout << "t1: " << t1 << endl;
		cout << "t1.sideA() = " << t1.sideA() << endl;
		cout << "t1.sideB() = " << t1.sideB() << endl;
		cout << "t1.sideC() = " << t1.sideC() << endl;
		
		cout << "\n====== COPY CONSTRUCTOR ======" << endl;
		cout << "t1: " << t1 << endl;
		Triangle t1Copy(t1);
		cout << "after Triangle t1Copy(t1), t1Copy: " << t1Copy << endl;
		cout << "t1: " << t1 << endl;
		Triangle t1FullCopy(t1);
		cout << "after Triangle t1FullCopy(t1), t1FullCopy: " << t1FullCopy << endl;

		cout << "\n====== ASSIGNMENT ======" << endl;
		// cannot assign to a constant
		// t0 = t1;
		// t0.assign(t1);
		cout << "t1: " << t1 << ", t2: " << t2 << endl;
		cout << "after t1 = t2, t1 becomes " << (t1 = t2) << ", t2 stays " << t2 << endl;
		
		cout << "t1: " << t1 << ", t1FullCopy: " << t1FullCopy << endl;
		cout << "after t1.assign(t1FullCopy), t1 becomes " << (t1.assign(t1FullCopy)) << endl;
		cout << "t1FullCopy stays " << t1FullCopy << endl;

		cout << "\n=== assign itself ===" << endl;
		cout << "t1: " << t1 << endl;
		cout << "after t1 = t1, t1 becomes " << (t1 = t1) << endl;
		cout << "after t1.assign(t1), t1 becomes " << (t1.assign(t1)) << endl;
		
		cout << "\n====== PERIMETER ======" << endl;
		cout << "t0: " << t0 << endl;
		cout << "t0.perimeter() = " << t0.perimeter() << endl;
		cout << "t1: " << t1 << endl;
		cout << "t1.perimeter() = " << t1.perimeter() << endl;

		cout << "\n====== AREA ======" << endl;
		cout << "t0: " << t0 << endl;
		cout << "t0.area() = " << t0.area() << endl;
		cout << "t1: " << t1 << endl;
		cout << "t1.area() = " << t1.area() << endl;

		cout << "\n====== SIDE'S LENGTH ======" << endl;
		cout << "t2: " << t2 << endl;
		cout << "t2.lengthA() = " << t2.lengthA() << endl;
		cout << "t2.lengthB() = " << t2.lengthB() << endl;
		cout << "t2.lengthC() = " << t2.lengthC() << endl;

		cout << "\n====== HEIGHTS ======" << endl;
		cout << "t1: " << t1 << endl;
		cout << "t1.heightA() = " << t1.heightA() << endl;
		cout << "t1.heightB() = " << t1.heightB() << endl;
		cout << "t1.heightC() = " << t1.heightC() << endl << endl;
		cout << "t2: " << t2 << endl;
		cout << "t2.heightA() = " << t2.heightA() << endl;
		cout << "t2.heightB() = " << t2.heightB() << endl;
		cout << "t2.heightC() = " << t2.heightC() << endl;

		cout << "\n====== MEDIANS ======" << endl;
		// obtuse triangle
		cout << "t1: " << t1 << endl;
		// use separate method for every median
		cout << "t1.medianA() = " << t1.medianA() << endl;
		cout << "t1.medianB() = " << t1.medianB() << endl;
		cout << "t1.medianC() = " << t1.medianC() << endl << endl;
		// acute triangle
		cout << "t2: " << t2 << endl;
		// use one method for all medians
		cout << "t2.median(t2.sideA()) = " << t2.median(t2.sideA()) << endl;
		cout << "t2.median(t2.sideB()) = " << t2.median(t2.sideB()) << endl;
		cout << "t2.median(t2.sideC()) = " << t2.median(t2.sideC()) << endl;

		cout << "\n====== MODIFIERS OF APICES ======" << endl;
		cout << "t1: " << t1 << endl;
		Point a1(3, 0);
		Point b1(0, 0);
		Point c1(0, 2);
		cout << "a1: " << a1 << endl;
		cout << "b1: " << b1 << endl;
		cout << "c1: " << c1 << endl;
		t1.setApexA(a1);
		t1.setApexB(b1);
		t1.setApexC(c1);
		cout << "after t1.setApexA(a1), t1.setApexB(b1) and t1.setApexC(c1)" << endl;
		cout << "t1 becomes " << t1 << endl;

		cout << endl << "Only apices of a triangle can be modified." << endl;
		cout << "When they are modified, sides, heights and medians change too." << endl << endl;

		// new sides
		cout << "t1.sideA() = " << t1.sideA() << endl;
		cout << "t1.sideB() = " << t1.sideB() << endl;
		cout << "t1.sideC() = " << t1.sideC() << endl << endl;

		// new heights
		cout << "t1.heightA() = " << t1.heightA() << endl;
		cout << "t1.heightB() = " << t1.heightB() << endl;
		cout << "t1.heightC() = " << t1.heightC() << endl << endl;

		// new medians
		// right triangle
		Triangle::Segment reversedSideA = Triangle::Segment::Segment(t1.sideA().end(), t1.sideA().start());
		Triangle::Segment reversedSideB = Triangle::Segment::Segment(t1.sideB().end(), t1.sideB().start());
		Triangle::Segment reversedSideC = Triangle::Segment::Segment(t1.sideC().end(), t1.sideC().start());
		cout << "reversedSideA: " << reversedSideA << endl;
		cout << "reversedSideB: " << reversedSideB << endl;
		cout << "reversedSideC: " << reversedSideC << endl;
		// use one method for all medians and pass reversed sides to it
		cout << "t1.median(reversedSideA) = " << t1.median(reversedSideA) << endl;
		cout << "t1.median(reversedSideB) = " << t1.median(reversedSideB) << endl;
		cout << "t1.median(reversedSideC) = " << t1.median(reversedSideC) << endl << endl;
	} catch (const Triangle::BadTriangle& err) {
		cerr << "Error! " << err.message() << ": " << err.a() << ", " <<
			err.b() << ", " << err.c() << endl;
	}

	try {
		cout << "\n=== trying to construct triangle with area 0 ===" << endl;
		Triangle t4(0, 0, 1, 1, 2, 2); // area is 0
	} catch (const Triangle::BadTriangle& err) {
		cerr << "Error! " << err.message() << ": " << err.a() << ", " <<
			err.b() << ", " << err.c() << endl;
	}

	try {
		cout << "\n=== trying to find median for non-existent side ===" << endl;
		Triangle t(0, 0, 1, 1, -1, 1);
		Triangle::Segment seg = Triangle::Segment::Segment(100, 5);
		Triangle::Segment med = t.median(seg);
	} catch (const Triangle::BadTriangle& err) {
		cerr << "Error! " << err.message() << ": " << err.a() << ", " <<
			err.b() << ", " << err.c() << endl;
	}
}

void testMedians() {
	try {
		Triangle t1(-3, 0, 0, 0, -5, 2); // by coordinates
		Point a;
		Point b(1, 1);
		Point c(-1, 1);
		Triangle t2(a, b, c); // by points

		cout << "====== medians ======" << endl;
		// obtuse triangle
		cout << "t1: " << t1 << endl;
		// use separate method for every median
		cout << "t1.medianA() = " << t1.medianA() << endl;
		cout << "t1.medianB() = " << t1.medianB() << endl;
		cout << "t1.medianC() = " << t1.medianC() << endl << endl;
		// acute triangle
		cout << "t2: " << t2 << endl;
		// use one method for all medians
		cout << "t2.median(t2.sideA()) = " << t2.median(t2.sideA()) << endl;
		cout << "t2.median(t2.sideB()) = " << t2.median(t2.sideB()) << endl;
		cout << "t2.median(t2.sideC()) = " << t2.median(t2.sideC()) << endl;

		cout << "\n====== modify apices ======" << endl;
		cout << "t1: " << t1 << endl;
		Point a1(3, 0);
		Point b1(0, 0);
		Point c1(0, 2);
		cout << "a1: " << a1 << ", ";
		cout << "b1: " << b1 << ", ";
		cout << "c1: " << c1 << endl;
		t1.setApexA(a1);
		t1.setApexB(b1);
		t1.setApexC(c1);
		cout << "after t1.setApexA(a1), t1.setApexB(b1) and t1.setApexC(c1)" << endl;
		cout << "t1: " << t1 << endl;

		cout << endl << "Only apices of a triangle can be modified." << endl;
		cout << "When they are modified, sides, heights and medians change too." << endl << endl;

		// new sides
		cout << "t1.sideA() = " << t1.sideA() << endl;
		cout << "t1.sideB() = " << t1.sideB() << endl;
		cout << "t1.sideC() = " << t1.sideC() << endl << endl;

		// new medians
		// right triangle
		Triangle::Segment reversedSideA = Triangle::Segment::Segment(t1.sideA().end(), t1.sideA().start());
		Triangle::Segment reversedSideB = Triangle::Segment::Segment(t1.sideB().end(), t1.sideB().start());
		Triangle::Segment reversedSideC = Triangle::Segment::Segment(t1.sideC().end(), t1.sideC().start());
		cout << "reversedSideA: " << reversedSideA << endl;
		cout << "reversedSideB: " << reversedSideB << endl;
		cout << "reversedSideC: " << reversedSideC << endl;
		// use one method for all medians and pass reversed sides to it
		// the order of points is not important for a segment, so it works for reversed sides too
		cout << "t1.median(reversedSideA) = " << t1.median(reversedSideA) << endl;
		cout << "t1.median(reversedSideB) = " << t1.median(reversedSideB) << endl;
		cout << "t1.median(reversedSideC) = " << t1.median(reversedSideC) << endl << endl;
	} catch (const Triangle::BadTriangle& err) {
		cerr << "Error! " << err.message() << ": " << err.a() << ", " <<
			err.b() << ", " << err.c() << endl;
	}

	try {
		cout << "\n=== trying to find median for non-existent side ===" << endl;
		Triangle t(0, 0, 1, 1, -1, 1);
		Triangle::Segment seg = Triangle::Segment::Segment(100, 5);
		Triangle::Segment med = t.median(seg);
	} catch (const Triangle::BadTriangle& err) {
		cerr << "Error! " << err.message() << ": " << err.a() << ", " <<
			err.b() << ", " << err.c() << endl;
	}

}

void testWeekDays() {
	Date::setDefault(); // to make sure default date is today
	Date today;
	Date date(today);
	Calendar calendar;
	// print todays weekday
	cout << "today, " << date << ": " << calendar.weekDayName(date) << endl;
	date.setDay(1);
	// print weekdays for a week, starting with first day of this month
	for (int i = 0; i < 7; i++) {
		cout << date << ": " << calendar.weekDayName(date) << endl;
		++date;
	}
	cout << "-----------------" << endl;
	date.setDYear(date.year() + 1);
	// print weekdays for a week, starting with 8 day of this month next year
	for (int i = 0; i < 7; i++) {
		cout << date << ": " << calendar.weekDayName(date) << endl;
		++date;
	}
	cout << "-----------------" << endl;
	date = today;
	date.setMonth(1);
	date.setDay(1);
	// print weekdays for a week, starting with 1 jan
	for (int i = 0; i < 7; i++) {
		cout << date << ": " << calendar.weekDayName(date) << endl;
		++date;
	}
}

void testHolidays() {
	Calendar calendarThisYear;
	int thisYear = 2018;
	cout << calendarThisYear.year() << " HOLIDAYS:" << endl;
	calendarThisYear.printHolidays();
	cout << "---------------------" << endl;

	Calendar calendarPrevYear(thisYear - 1);
	cout << calendarPrevYear.year() << " HOLIDAYS:" << endl;
	calendarPrevYear.printHolidays();
	cout << "---------------------" << endl;

	Calendar calendarNextYear(thisYear + 1);
	cout << calendarNextYear.year() << " HOLIDAYS:" << endl;
	calendarNextYear.printHolidays();
	cout << "---------------------" << endl;

	Date newYear(1, 1, thisYear);
	Date catholicChristmas(25, 12, thisYear);
	Date today;
	cout << boolalpha;
	cout << newYear << " is holiday: " << calendarThisYear.holiday(newYear) <<
		", is workday(): " << calendarThisYear.workday(newYear) << endl;
	cout << catholicChristmas << " is holiday: " << calendarThisYear.holiday(catholicChristmas) <<
		", is workday(): " << calendarThisYear.workday(catholicChristmas) << endl;
	cout << today << " is holiday: " << calendarThisYear.holiday(today) <<
		", is workday(): " << calendarThisYear.workday(today) << endl;

	for (int i = 0; i < 20; i++) {
		cout << today << " is workday(): " << calendarThisYear.workday(today) << endl;
		++today;
	}
}

void testAlarm() {
	cout << "Alarm will signal in 5 seconds" << endl;
	Time time = Time::now();
	time.setSeconds(time.seconds() + 5); // 5 seconds from now
	Date::setDefault(); // make sure default date is today
	Date today; // initialize using default constructor
	Alarm a("alarm message", today, time);
}

void testRegularAlarm() {
	cout << "Alarm will signal in 5 seconds" << endl;
	Time time = Time::now();
	time.setSeconds(time.seconds() + 5); // 5 seconds from now
	Date::setDefault(); // make sure default date is today
	Date today; // initialize using default constructor
	Alarm a("time to work", time);

	// I tested on holidays too (by placing "today" into an array of holidays)
	// it works (= doesn't signal, because not a workday)
}

void testPair() {
	Pair<int, string> pi1(1, "one");
	Pair<int, string> pi2(2, "two");
	Pair<int, string> pi3(3, "one");
	
	Pair<int, string> pi1Copy(pi1);

	cout << boolalpha;
	cout << pi1 << " == " << pi2 << " : " << (pi1 == pi2) << endl;
	cout << pi1 << " == " << pi1Copy << " : " << (pi1 == pi1Copy) << endl;
	cout << pi1 << " != " << pi1 << " : " << (pi1 != pi1) << endl;
	cout << pi1 << " != " << pi3 << " : " << (pi1 == pi3) << endl;

	cout << pi1 << " <  " << pi2 << " : " << (pi1 < pi2) << endl;
	cout << pi2 << " >  " << pi3 << " : " << (pi2 > pi3) << endl;
	cout << pi1 << " <= " << pi1 << " : " << (pi1 <= pi1) << endl;
	cout << pi3 << " >= " << pi1 << " : " << (pi3 >= pi1) << endl;

	cout << "------------------------------------" << endl;

	Pair<char, char> pc1('a', 'A');
	Pair<char, char> pc2('b', 'B');
	Pair<char, char> pc3(pc1);
	pc3.value() = 'a';

	cout << pc1 << " == " << pc2 << " : " << (pc1 == pc2) << endl;
	cout << pc1 << " != " << pc3 << " : " << (pc1 != pc3) << endl;
	cout << pc1 << " >  " << pc2 << " : " << (pc1 > pc2) << endl;
	cout << pc1 << " <  " << pc2 << " : " << (pc1 < pc2) << endl;
	cout << pc1 << " >= " << pc2 << " : " << (pc1 >= pc2) << endl;
	cout << pc1 << " <= " << pc3 << " : " << (pc1 <= pc3) << endl;

	// cannot assign or copy different type
	// pc1 = pi1;
	// Pair<char, char> pc4(pi1);

}

template <typename Key, typename Value>
void testPush(PriorityStack<Key, Value>& stack, const Pair<Key, Value>& pair) {
	stack.push(pair);
	cout << pair << " pushed to stack" << endl;
}

template <typename Key, typename Value>
void testTop(const PriorityStack<Key, Value>& stack) {
	cout << "top of the stack: " << stack.top() << endl;
}

template <typename Key, typename Value>
void testPop(PriorityStack<Key, Value>& stack) {
	stack.pop();
	cout << "top of the stack popped" << endl;
}

void testStack(PriorityStack<int, string>& stack) {
	try {
		cout << boolalpha;
		cout << "stack.size(): " << stack.size() << endl;
		cout << "stack.empty(): " << stack.empty() << endl;

		testPush<int, string>(stack, Pair<int, string>(2, "2 first"));
		testTop<int, string>(stack);
		testPush<int, string>(stack, Pair<int, string>(1, "1 first"));
		testPush<int, string>(stack, Pair<int, string>(3, "3 first"));
		testTop<int, string>(stack);
		testPop<int, string>(stack);
		testTop<int, string>(stack);
		testPush<int, string>(stack, Pair<int, string>(3, "3 second"));
		testPush<int, string>(stack, Pair<int, string>(3, "3 third"));
		testTop<int, string>(stack);
		testPop<int, string>(stack);
		testTop<int, string>(stack);
		testPop<int, string>(stack);
		testTop<int, string>(stack);
		testPop<int, string>(stack);
		testTop<int, string>(stack);
		testPop<int, string>(stack);

		cout << "stack.size(): " << stack.size() << endl;
		cout << "stack.empty(): " << stack.empty() << endl;
		testPush<int, string>(stack, Pair<int, string>(2, "2 first"));
		testTop<int, string>(stack);
		testPop<int, string>(stack);

	} catch (const PriorityStack<int, string>::BadStack& bs) {
		cerr << "Error: ";
		bs.diagnose();
		cerr << endl;
	}

	cout << "\n=== TRY to get TOP of the EMPTY STACK ===" << endl;
	try {
		string topVal = stack.top();
	} catch (const PriorityStack<int, string>::BadStack& bs) {
		cerr << "Error: ";
		bs.diagnose();
		cerr << endl;
	}

	cout << "\n=== TRY to POP from the EMPTY STACK ===" << endl;
	try {
		stack.pop();
	} catch (const PriorityStack<int, string>::BadStack& bs) {
		cerr << "Error: ";
		bs.diagnose();
		cerr << endl;
	}

}