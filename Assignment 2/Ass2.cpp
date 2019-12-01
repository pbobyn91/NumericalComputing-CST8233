/************************************************
Filename: Ass2.cpp
Version: 1.0
Student Name: Patrick Bobyn
Student Number: 040889706
Course Name: Numerical Computing
Course Code:CST8233
Lab Section Number: 302
Assignment Name: Assignment 2: Moore's Law
Due Date: 2019/11/15
Submission Date:2019/11/12
Professor's Name: Abdullah Kadri
This program does a linear regression using information from a text file. The specific file used for this was called Moore.txt,
so please that same template to run this.
**********************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

using namespace std;

class file {
public:
	// class variables
	ifstream fp;			// opened file 
	char filename[25] = "";		// file name
	double a = 0, b = 0;	// 2 constants for the equation
	int lines = 0;			// number of liness

	// method declarations
	void print();
	void extrapolation();
};

void moore();

/***********************************************
Function name: main
Purpose: main function

In parameters: None
Out Parameters: 0 for success 
Version: 1.0
Author: Patrick Bobyn
************************************************/
int main() {
	
	char option = ' '; // user option for a switch case 

	// print title 
	cout << "LEAST_SQUARES LINEAR REGRESSION" << endl << endl;

	do {
		// print menu
		cout << "MENU\n1. Exponential Fit\n2. Quit" << endl;
		cin >> option;

		switch (option) {
		case '1':				// user picked option 1
			moore();
			break;
		case '2':				// user picked to quit 
			cout << "Quitting";
			break;
		default:				// default option, not an option
			cout << "Pick Valid Option" << endl;
			break;
		}
	} while (option != '2');
	return 0;
}

/***********************************************
Function name: moore()
Purpose: This function opens the file and prints it out to the screen. 

In parameters: None
Out Parameters: void
Version: 1.0
Author: Patrick Bobyn
************************************************/
void moore() {

	char option = ' '; // user option for later switch case
	file f;

	// get filename 
	cout << "Please enter the name of the file to open: ";
	cin >> f.filename;

	// open file if possible 
	f.fp.open(f.filename);
	if (!f.fp.good()) {
		cout << "404 File Not Found" << endl;
		return;
	}

	// print the files contents
	f.print();

	// print out menu with options for the file
	do {
		// print menu
		cout << endl << "MENU\n1. Extrapolation\n2. Main Menu" << endl;
		cin >> option;

		switch (option) {
		case '1':					// Extrapolate from the file
			f.extrapolation();
			break;
		case '2':					// return to main menu
			cout << "Returning to Main Menu" << endl;
			break;
		default:					// default, not an option
			cout << "Not an Option" << endl;
			break;
		}
	} while (option != '2');
}

/***********************************************
Function name: file::print()
Purpose: This function is called by moore, it prints out the file and then it stores the variables for the regression in the class file.
It then prints another menu out.

In parameters: None
Out Parameters: void
Version: 1.0
Author: Patrick Bobyn
************************************************/
void file::print() {

	string stryear, strtrans, name;
	double trans, sumyear = 0, sumtrans = 0, sumyeartrans = 0, sumyearsquared = 0, a0;
	int year;

	this->fp >> stryear >> strtrans >> name;
	cout << stryear << "\t" << strtrans << "\t" << name << endl;

	// read from file 
	while (this->fp >> year >> trans >> name) {
		// print out line 
		cout << fixed << year;
		cout << "\t" << scientific << trans << "\t" << name << endl;

		sumyear += year;
		sumtrans += log(trans);
		sumyeartrans += (year * log(trans));
		sumyearsquared += pow(year, 2);

		this->lines++;
	}

	this->b = ((this->lines * sumyeartrans) - (sumyear * sumtrans)) / (this->lines * sumyearsquared - (sumyear * sumyear));
	a0 = sumtrans/this->lines - this->b * (sumyear - ((double)1970 * this->lines)) / this->lines;
	this->a = exp(a0);

	// print out values
	cout << "\nThere are " << this->lines << " records." << endl << endl;
	cout << "Linear Regression Fit: Transistor Count = " << scientific << this->a << " * exp ( " << this->b << " * (year - 1970))" << endl << endl;
}

/***********************************************
Function name: extrapolation()
Purpose: This method was called from the class moore(), after the data has been saved for regression this method will estimate
the later points.

In parameters: None
Out Parameters: void
Version: 1.0
Author: Patrick Bobyn
************************************************/
void file::extrapolation() {
	
	int year;		// year to extrapolate to
	double transistor, transprev;	// # of transistors in specified year
	double rate;

	cout << "\nPlease enter the year to extrapolate to: ";
	if (cin >> year) {}
	else if (cin.fail()) {
		cin.clear();
		cout << "Invalid input";
		return;
	}

	// print out calculation
	cout << "Year: " << fixed << year << endl;
	transistor = this->a * exp(this->b * ((double)year - 1970));		// calculate the transistors
	cout << "Transistor Count: " << scientific << transistor << endl;
	rate = (this->a * this->b) * exp(this->b * ((double)year - 1970));			// calculate the growth rate
	cout << "Rate of Count Increase: " << scientific << rate << " Transistors/year" << endl << endl;
}