// myDate.h
#ifndef MYDATE_H
#define MYDATE_H
#include <iostream>
using namespace std;

class myDate
{
public:
	myDate(); // default constructor
	myDate(int M, int D, int Y); // overload constructor
	void display();
	void increaseDate(int N);
	void decreaseDate(int N);
	int daysBetween(myDate D);
	int getMonth();
	int getDay();
	int getYear();
	int dayOfYear();
	string dayName();

	// Assignment 3 changes
	void printdate();
	int julian();

private:
	int month;
	int day;
	int year;
};

#endif

