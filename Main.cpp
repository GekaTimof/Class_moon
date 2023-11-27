#include <iostream>
#include <string> 
#include <fstream>
#include <time.h>
#include "Moon.h"


using namespace std;
// Start program hear
int main(void) {
	// posetion of file with moon cordinates
	const string file_name = "../Moon_info/moon";

	// take date from user
	//string date_text;
	//cout << "enter the date in format - dd.mm.yyyy \n";
	//cin >> date_text;
	//Date user_date = date_text;

	// take test date
	Date user_date = "09.09.1999";

	// final verson of file name
	string file = file_name + user_date.TakeYear() + ".dat";

	cout << "user date	" << user_date << "\n\n";




	// try to open file
	fstream fileStream;
	fileStream.open(file);
	// test result of file opening
	if (fileStream.fail()) {
		cout << "Sorry this year not include in this database";
	}
	else {
		fileStream.close();
		Moon moon;
		moon = user_date;

		// start time counting
		clock_t tStart = clock();
		// do function
		moon.TakeInfo(file);
		// stop time counting
		double time = (double)(clock() - tStart) / CLOCKS_PER_SEC;
		cout << "final time  " << time << '\n';

		moon.ShowInfo();
	}

	cout << "\n the end of programm \n";
}