#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "Moon.h"

using namespace std;
// -------------------------------- Class Date --------------------------------
// take year
string Date::TakeYear() {
	return to_string(this->year);
}

// take day
string Date::TakeDay() {
	return to_string(this->day);
}


// enter data
Date::Date(const string data) {
	int i = 0;
	if (data.length() >= 8) {
		// take day
		while ((data[i] >= '0') && (data[i] <= '9')) {
			day = day * 10 + data[i] - '0';
			i++;
		}
		i++;
		// take month
		while ((data[i] >= '0') && (data[i] <= '9')) {
			month = month * 10 + data[i] - '0';
			i++;
		}
		i++;

		// take year
		while ((data[i] >= '0') && (data[i] <= '9')) {
			year = year * 10 + data[i] - '0';
			i++;
		}
	}
}


// enter data
Date::Date(const char* data) {
	// finding lenght of data array
	int Size = 0;
	while (data[Size] != '\0') Size++;

	int i = 0;

	if (Size >= 8) {
		// take day
		while ((data[i] >= '0') && (data[i] <= '9')) {
			day = day * 10 + data[i] - '0';
			i++;
		}
		i++;
		// take month
		while ((data[i] >= '0') && (data[i] <= '9')) {
			month = month * 10 + data[i] - '0';
			i++;
		}
		i++;

		// take year
		while ((data[i] >= '0') && (data[i] <= '9')) {
			year = year * 10 + data[i] - '0';
			i++;
		}
	}
}

//  print data operator
ostream& operator << (ostream& out, const Date& date) {
	out << to_string(date.year) << " ";
	out << to_string(date.month) << " ";
	out << to_string(date.day);
	return out;
}


// operator =
Date Date::operator = (const Date& date) {
	this->day = date.day;
	this->month = date.month;
	this->year = date.year;
	return *this;
}


// count number of days from year start
int Date::DayNum() {
	// count total number of  days
	int total_days = 0;

	// finding today year tipe
	if (year % 4 == 0) {
		// days in today year (leap year)
		for (int m = 1; m < month; m++) {
			total_days += leap_year[m];
		}
	}
	else {
		// days in today year (normal year)
		for (int m = 1; m < month; m++) {
			total_days += normal_year[m];
		}
	}
	// days in today month
	total_days += day;
	return total_days;
}


// -------------------------------- Class Time --------------------------------
// enter time
Time::Time(const string data) {
	int i = 0;
	if (data.length() >= 8) {
		// take hour
		while ((data[i] >= '0') && (data[i] <= '9') && (i < data.length())) {
			hour = hour * 10 + data[i] - '0';
			i++;
		}
		i++;

		// take minute
		while ((data[i] >= '0') && (data[i] <= '9') && (i < data.length())) {
			minute = minute * 10 + data[i] - '0';
			i++;
		}
		i++;

		// take second
		while ((data[i] >= '0') && (data[i] <= '9') && (i < data.length())) {
			second = second * 10 + data[i] - '0';
			i++;
		}
	}
	else if (data.length() == 6) {
		// take hour
		while ((data[i] >= '0') && (data[i] <= '9') && (i < 2)) {
			hour = hour * 10 + data[i] - '0';
			i++;
		}

		// take minute
		while ((data[i] >= '0') && (data[i] <= '9') && (i < 4)) {
			minute = minute * 10 + data[i] - '0';
			i++;
		}

		// take second
		while ((data[i] >= '0') && (data[i] <= '9') && (i < 6)) {
			second = second * 10 + data[i] - '0';
			i++;
		}
	}
}


// Transform hour to Time
Time::Time(double Hours) {
	if (Hours >= 1.0) {
		hour = Hours ;
		Hours -= hour;
	}

	if (Hours >= 1.0 / 60.0) {
		minute = Hours / (1.0 / 60.0);
		Hours -= minute / 60.0;
	}

	if (Hours >= 1.0 / 3600.0) {
		second = Hours / (1.0 / 3600.0);
	}
}


//  print time operator
ostream& operator << (ostream& out, const Time& time) {
	out << to_string(time.hour) << " ";
	out << to_string(time.minute) << " ";
	out << to_string(time.second);
	return out;
}


// Transfor Time to hours
double Time::Time_to_hours() {
		return (this->hour + this->minute / 60.0 + this->second / 3600.0);
}




// -------------------------------- Class Moon --------------------------------
// take date
Date Moon::TakeDate() {
	return this->day_date;
}


// enter date
Moon::Moon(Date date) {
	day_date = date;
}


// take informatin about moon in date from file
void Moon::TakeInfo(string file) {
	// try to open file
	fstream fileStream;
	fileStream.open(file);

	int start = 0;
	// test result of file opening
	if (!(fileStream.fail())) {
		int num = 0;
		string line;
		// skip 0 and 1 lines
		getline(fileStream, line);
		getline(fileStream, line);

		// take 2 line
		num = 2;
		getline(fileStream, line);

		// take time step from this file
		Time step = line.substr(9, 6);
		//cout << "step = " << step << "\n";			// -> step

		// line where day start
		start = this->Steps_for_date(step);
		cout << "start = " << start << "\n";		// -> start

		fileStream.close();
	}

	fileStream.open(file);
	// test result of file opening
	if (!(fileStream.fail())) {
		string line;

		if (start != 0) {
			fileStream.seekg(ios::beg);
			for (int i = 0; i < start; ++i) {
				fileStream.ignore(numeric_limits<streamsize>::max(), '\n');
			}



			// arguments that contain time
			double t0 = 0, t1 = 0, t2 = 0, t3 = 0;
			// arguments that contain moon corners
			double c0 = -90, c1 = -90, c2 = -90, c3 = -90 ;


			// get line and test it untill we find all moon arguments
			while (this->IsNotFull() and (getline(fileStream, line))) {
				//cout << line << "\n";								// -> line

				// move values and create empty arguments for new datas
				t0 = t1; t1 = t2; t2 = t3; t3 = 0;
				c0 = c1; c1 = c2; c2 = c3; c3 = -90;


				// container to contain arguments from line
				string container = "";

				// take datas from line and convert it to double
				int i = 0;
				int x = 0;
				bool swch = true;

				while (x < 5) {
					if (((line[i] >= '0') && (line[i] <= '9')) || (line[i] == '-') || (line[i] == '.')) {
						// add simbol in container
						container += line[i];

						// change the switch 
						swch = true;
					}
					else {

						// if we finished crating container
						if (swch) {
							x++;
							swch = false;
						switch (x) {
							// if we have time in container
						case 3:
							t3 = stod(container);
							//cout << t3 << "\n";					// -> t3
 							break;

							// if we have corner in container
						case 5:
							c3 = stod(container);
							//cout << c3 << "\n";					// -> c3
							break;

						}

						// reset container
						container = "";
						}
					}
					i++;
				}

				// test datas that we took
				// moonrise checking
				if ((c3 > -90 and c2 > -90) and (c2 < 0 and c3 > 0)) {
					//cout << "t2 = " << t2 << "	t3 = " << t3 << "	c2 = " << c2 << "	c3 = " << c3 << '\n';
					//cout << "moon rise = " << t2 + ((t3 - t2) * abs(c2 / abs(c2 - c3))) << '\n';

					// transform date in hours to Time and save it
					this->moonrise = (t2 + ((t3 - t2) * abs(c2 / abs(c2 - c3))));
					//cout << this->moonrise << "  =  " << this->moonrise.Time_to_hours() <<  '\n\n';
				}

				// moonset checking
				if ((c3 > -90 and c2 > -90) and (c2 > 0 and c3 < 0)) {
					//cout << "t2 = " << t2 << "	t3 = " << t3 << "	c2 = " << c2 << "	c3 = " << c3 << '\n';
					//cout << "moon set = " << t2 + ((t3 - t2) * abs(c2 / (abs(c3 - c2)))) << '\n';

					// transform date in hours to Time and save it
					this->moonset = (t2 + ((t3 - t2) * abs(c2 / abs(c2 - c3))));
					//cout << this->moonrise << "  =  " << this->moonrise.Time_to_hours() <<  '\n\n';
				}

				// moon on the peak cheking
				if ((c3 > -90 and c2 > -90 and c1 > -90 and c0 > -90) and ((c0 < c1 and c1 < c2 and c2 > c3) or (c0 < c1 and c1 > c2 and c2 > c3) or (c0 < c1 and c1 == c2 and c2 > c3)) and (this->peak.Time_to_hours() == 0)) {
					// we have peak between c1 and c2
					//cout << c0 << " " << c1 << " " << c2 << " " << c3 << "\n";

					this->peak = ((t1 + t2) / 2);
					//cout << this->peak << "\n";
				}

			}
		}
		else {
			cout << "Broblem with start counting";
		}
	}
	else {
		cout << "Sorry you have broblem with conection";
	}


}


// Count number of steps that need to reach this date (we start counting from year start)
int Moon::Steps_for_date(Time step) {
	// divide the number of days by a step and round it up
	//cout << step.Time_to_hours() << "\n";
	return (((day_date.DayNum()-1) * 24) / step.Time_to_hours() + 1);	// !!! this possetion isn't absolutly right
}

// checking - whether the class values are filled in or not
bool Moon::IsNotFull() {
	return (not(moonrise.Time_to_hours() > 0 and peak.Time_to_hours() > 0 and moonset.Time_to_hours() > 0));
}

// show information ablout moonrise moonset and moon peak
void Moon::ShowInfo() {
	cout << "\n";
	if (not(IsNotFull())) {
		cout << "moonrise = " << moonrise << "\n";
		cout << "moonset = " << moonset << "\n";
		cout << "moon on the peak = " << peak << "\n";
	}
	else {
		cout << "not enough information";
	}

}
