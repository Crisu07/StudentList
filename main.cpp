//  main.cpp
// 	Chris Nguyen
//	CECS 282-04 (Tue/Thur)
//	Prog 3 – Student Structs
// 	Due 10/12/2021
// 
//  I certify that this program is my own original work. I did not copy any part of this program from 
//  any other source. I further certify that I typed each and every line of code in this program.
#include "myDate.h" // added 2 functions to mydate(at the bottom of file): return julian number and print bday
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip> // used for formatting the output
#include <algorithm> // used for sorting strings using sort() and find()
using namespace std;

struct Student
{
	char name[18];
	int studentid;
	char grade;
	myDate birthday;
	string hometown;
};

Student* createStudent(string n, int id, char g, myDate bday, string home)
{
	struct Student* stud = new Student;
	strcpy_s(stud->name, n.c_str());
	stud->studentid = id;
	stud->grade = g;
	stud->birthday = bday;
	stud->hometown = home;
	return stud;
}

// display menu options
void menu()
{
	cout << "Student Menu" << endl;
	cout << "1) Sort by Name" << endl;
	cout << "2) Sort by StudentID" << endl;
	cout << "3) Sort by Grade" << endl;
	cout << "4) Sort by Birthday" << endl;
	cout << "5) Sort by Hometown" << endl;
	cout << "6) Exit" << endl;
}

// Sort by names
void sortName(Student* myClass[])
{
	/* (note to self) strcmp will compare two cstrings letter by letter and return a value to check
	less than 0 that means the first cstring goes before the second cstring
	equal to 0 then the cstrings are the exact same
	more than 0 than the first cstring is alphabetically greater than the second (indiciating a swap) */
	for (int i = 0; i < 10; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			int cname = strcmp(myClass[i]->name, myClass[j]->name);
			if (cname > 0)
			{
				Student* temp = myClass[i];
				myClass[i] = myClass[j];
				myClass[j] = temp;
			}
		}
	}
}

// Sort by IDs
void sortID(Student* myClass[])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			if (myClass[i]->studentid > myClass[j]->studentid) // if the student id is less than the one in front, swap
			{
				Student* temp = myClass[i];
				myClass[i] = myClass[j];
				myClass[j] = temp;
			}
		}
	}
}

// Sort by grades
void sortGrade(Student* myClass[])
{
	// asii values -> A = 65, B = 66, etc.
	for (int i = 0; i < 10; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			if (myClass[i]->grade > myClass[j]->grade) // order should be ABCDF so swap according to ascii values
			{
				Student* temp = myClass[i];
				myClass[i] = myClass[j];
				myClass[j] = temp;
			}
		}
	}
}

// Sort by birthdays
void sortBday(Student* myClass[])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (myClass[i]->birthday.julian() < myClass[j]->birthday.julian()) // if amount of days since julian date began is less than, swap
			{
				Student* temp = myClass[i];
				myClass[i] = myClass[j];
				myClass[j] = temp;
			}
		}
	}
}

// Sort by hometown
void sortHome(Student* myClass[])
{
	string homes[10];
	for (int i = 0; i < 10; i++)
	{
		homes[i] = myClass[i]->hometown;
	}
	sort(homes, homes+10); // sorts homes alphabetically using the built in sort() function

	// Edit student array to match the sorted homes array
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (homes[i] == myClass[j]->hometown) // go through homes by index and if the hometown matches then change to that order 
			{
				Student* temp = myClass[i];
				myClass[i] = myClass[j];
				myClass[j] = temp;
			}
		}
	}
}

// Output
void print(Student* myClass[])
{
	// setw should be different for each to line up together, find correct amounts
	cout << left << setw(20) << "Name" << setw(20) << "Student ID" << setw(20) << "Grade" << setw(20) << "Birthday" << setw(10) << "Home Town" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << left << setw(20) << myClass[i]->name << setw(20) << myClass[i]->studentid << setw(20) << myClass[i]->grade << setw(20);
		myClass[i]->birthday.printdate();
		cout << setw(40) << myClass[i]->hometown << endl;
	}
}

// Generate random valid bdays
myDate randbday()
{
	int m = rand() % 12 + 1; // random month 1 - 12
	int d = rand() % 31 + 1; // random day 1 - 31
	int y = rand() % (2024 - 2000 + 1) + 2000; // random year between 2000-2024

	myDate bday(m, d, y); // myDate should already account for valid dates -> if it is 5/11/1959 then it was an invalid date
	if (bday.getMonth() != 5 and bday.getDay() != 5 and bday.getYear() != 1959)
	{
		return bday;
	}
	else // if invalid generate a valid bday
	{
		randbday();
	}
}

// Generate random grades
char randgrade()
{
	char grades[5] = { 'A', 'B', 'C', 'D', 'F' };
	int g = rand() % 5; // random num from 0-5
	return grades[g];
}

int main()
{
	srand(time(NULL));
	int ids[10]; // array of ids to check for unique-ness
	int id;
	bool unique;

	// Generating unique ids
	for (int i = 0; i < 10; i++)
	{
		id = rand() % (999 - 100 + 1) + 100;
		/*(note to self) find() is part of include algorithms and will find a value within an array
		begin(arrayname) is starting index and end() is end index
		sid is the value to check for
		if the value is found, return index of that value, else return the end index*/
		unique = find(begin(ids), end(ids), id) == end(ids); // if it returns the end index then the value is unique
		while (not unique) // keep generating new number if the value is NOT unique
		{
			id = rand() % (999 - 100 + 1) + 100;
		}
		ids[i] = id; // if it is unique store to the array
	}

	Student* myClass[10]; // array of pointers for 10 students

	myClass[0] = createStudent("Kazuya Mishima", ids[0], randgrade(), randbday(), "Tekken");
	myClass[1] = createStudent("Joker Arsene", ids[1], randgrade(), randbday(), "Persona");
	myClass[2] = createStudent("Min Min", ids[2], randgrade(), randbday(), "Arms");
	myClass[3] = createStudent("The Hero", ids[3], randgrade(), randbday(), "Dragon Quest");
	myClass[4] = createStudent("Byleth Eisner", ids[4], randgrade(), randbday(), "Fire Emblem");
	myClass[5] = createStudent("Banjo Kazooie", ids[5], randgrade(), randbday(), "Banjo & Kazooie");
	myClass[6] = createStudent("Terry Bogard", ids[6], randgrade(), randbday(), "Fatal Fury");
	myClass[7] = createStudent("Steve Alex", ids[7], randgrade(), randbday(), "Minecraft");
	myClass[8] = createStudent("Sephiroth", ids[8], randgrade(), randbday(), "Final Fantasy");
	myClass[9] = createStudent("Pyra Mythra", ids[9], randgrade(), randbday(), "Xenoblade");

	menu();
	int answer;
	cin >> answer;
	
	while (answer != 6) // if user inputs a 6, quit
	{
		if (answer == 1)
		{
			sortName(myClass);
			print(myClass);
			cout << endl;
			menu();
			cin >> answer;
		}
		else if (answer == 2)
		{
			sortID(myClass);
			print(myClass);
			cout << endl;
			menu();
			cin >> answer;
		}
		else if (answer == 3)
		{
			sortGrade(myClass);
			print(myClass);
			cout << endl;
			menu();
			cin >> answer;
		}
		else if (answer == 4)
		{
			sortBday(myClass);
			print(myClass);
			cout << endl;
			menu();
			cin >> answer;
		}
		else if (answer == 5)
		{
			sortHome(myClass);
			print(myClass);
			cout << endl;
			menu();
			cin >> answer;
		}
	}
}