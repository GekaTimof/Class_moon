#ifndef _MOONRISE
#define _MOONRISE

#include <iostream>
#include <string> 
using namespace std;
// -------------------------------- Class Date --------------------------------
// class for work with date
class Date {
	// days in normal year
	const int normal_year[13] = { 365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// days in leap year
	const int leap_year[13] = { 366, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// year
	int year = 0;
	// month
	int month = 0;
	// dasy
	int day = 0;

public:
	// enter date format - "DD.MM.YYYY"

	// enter no data 
	Date() {}

	// enter data from string
	Date(const string data);

	// enter data from array of char
	Date(const char* data);

	// print data operator
	friend ostream& operator << (ostream& out, const Date& data);


// operators

	// operator =
	Date operator = (const Date& date);

	// take year
	string TakeYear();

	// take day
	string TakeDay();

	// count number of days from year start
	int DayNum();
};

// -------------------------------- Class Time --------------------------------
// class for work with time
class Time {
	// hour
	int hour = 0;
	// minute
	int minute = 0;
	// second
	int second = 0;

public:
	// enter date format - "HHMMCC" or "HH.MM.CC"

	// enter no data 
	Time() {}

	// enter data from string
	Time(const string data);

	// Transform hour to Time
	Time(double hours);

	// print data operator
	friend ostream& operator << (ostream& out, const Time& data);

	// Transform Time to hours
	double Time_to_hours();



};

// -------------------------------- Class Moon --------------------------------
// class for work with moon cordinates
class Moon {
	// day when we need to make a calculation 
	Date day_date;

	// time when moon rise
	Time moonrise;
	// time when moon on the peak
	Time peak;
	// time when moon set
	Time moonset;

	// checking - whether the class values are filled in or not
	bool IsNotFull();

	// Count number of steps that need to reach this day_date (we start counting from year start)
	int Steps_for_date(Time steps);


public:
	// enter moon format - Date

	// enter no data
	Moon() {}

	// enter date
	Moon(Date date);

	// take day
	Date TakeDate();

	// take informatin about moon in date from file
	void TakeInfo(string file);

	// show information ablout moonrise moonset and moon peak
	void ShowInfo();
};
#endif