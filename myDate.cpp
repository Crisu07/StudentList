// myDate.cpp
#include "myDate.h"
#include <iostream>
#include <string>

using namespace std;

// pass in month day year, convert then reutrn Julian number
int Greg2Julian(int month, int day, int year)
{
	int I = year;
	int J = month;
	int K = day;
	int JD;

	JD = K - 32075 + 1461 * (I + 4800 + (J - 14) / 12) / 4 + 367 *
		(J - 2 - (J - 14) / 12 * 12) / 12 - 3 * ((I + 4900 + (J - 14) / 12) / 100) / 4;
	return JD;
}

// pass in Julian date and return correct month day year (starts from jan 1 4713bc/-4712)
void Julian2Greg(int JD, int& month, int& day, int& year)
{
	int I;
	int J;
	int K;
	int L = JD + 68569;
	int N = 4 * L / 146097;

	L = L - (146097 * N + 3) / 4;
	I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	J = 80 * L / 2447;
	K = L - 2447 * J / 80;
	L = J / 11;
	J = J + 2 - 12 * L;
	I = 100 * (N - 49) + I + L;

	// reassign values for references
	year = I;
	month = J;
	day = K;
}

bool leapcheck(int Y)
{
	if (Y % 4 == 0) // if the year is divisable by 4
	{
		if (Y % 100 == 0) // if it is divisable by 100
		{
			if (Y % 400 == 0) // if divisable by 400 then its a leap year
			{
				return true;
			}
			else // not a leap year
			{
				return false;
			}
		}
		else // if not divisable by 100 but by 4 then its a leap year
		{
			return true;
		}
	}
	else // not a leap year
	{
		return false;
	}
}

// default constructor: default date is May 11, 1959
myDate::myDate()
{
	month = 5;
	day = 11;
	year = 1959;
}

// overload constructor (can never have invalid date, if invalid date passed in, ignore all data and use default date)
myDate::myDate(int M, int D, int Y)
{
	int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // max num of days for each month

	if (Y > -4712) // Check for valid Years (4713 BC = -4712)
	{
		if ((M >= 1) and (M <= 12)) // Check for valid month range
		{
			if (M != 2) // Valid dates for every month besides Feb
			{
				int temp = days[M - 1];
				if ((D > 0) and (D <= temp)) // Check for valid days range depending on the month
				{
					month = M;
					day = D;
					year = Y;
				}
				else
				{
					month = 5;
					day = 11;
					year = 1959;
				}
			}
			else // if the month IS Feb
			{
				int temp = days[M - 1];
				if ((D > 0) and (D <= temp))
				{
					month = M;
					day = D;
					year = Y;
				}
				else if (D == 29) // if the day is 29, make sure the year is a leap year
				{
					bool check = leapcheck(Y);
					if (check) // if it is a leap year then valid date
					{
						month = M;
						day = D;
						year = Y;
					}
					else // if the day is 29 and it is not a leap year, invalid
					{
						month = 5;
						day = 11;
						year = 1959;
					}
				}
				else
				{
					month = 5;
					day = 11;
					year = 1959;
				}
			}
		}
		else
		{
			month = 5;
			day = 11;
			year = 1959;
		}
	}
	else // set to default date
	{
		month = 5;
		day = 11;
		year = 1959;
	}
}

// display date (do not print a line feed or new line)
void myDate::display()
{
	string mon[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	cout << mon[month - 1] << " " << day << ", " << year;
}

// increment days forward
void myDate::increaseDate(int N)
{
	int JDate = Greg2Julian(month, day, year);
	JDate += N;
	Julian2Greg(JDate, month, day, year);
}

// increment days back
void myDate::decreaseDate(int N)
{
	int JDate = Greg2Julian(month, day, year);
	JDate -= N;
	Julian2Greg(JDate, month, day, year);
}

int myDate::daysBetween(myDate D)
{
	int startD = Greg2Julian(month, day, year);
	int nextD = Greg2Julian(D.month, D.day, D.year);
	int daysbw = nextD - startD;
	return daysbw;
}

int myDate::getMonth()
{
	return month;
}

int myDate::getDay()
{
	return day;
}

int myDate::getYear()
{
	return year;
}

// return number of days since current year began
int myDate::dayOfYear()
{
	int startD = Greg2Julian(1, 1, year); // start of year
	int currD = Greg2Julian(month, day, year); // current date

	int days = 1; // account for Jan 1 as starting day
	days += currD - startD;
	return days;
}


string myDate::dayName()
{
	// jan 1 -4712 is a monday
	string week[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	int nameday = Greg2Julian(month, day, year);
	nameday = nameday % 7;
	// remainder of 0 would mean its a monday, 1 is tuesday and so on
	string dayofweek = week[nameday];
	return dayofweek;
}

// Functions/Changes added for Assignment 3
void myDate::printdate()
{
	string mon[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	string bday = mon[month - 1] + " " + to_string(day) + ", " + to_string(year);
	cout << bday;
}

int myDate::julian()
{
	int check = Greg2Julian(month, day, year);
	return check;
}