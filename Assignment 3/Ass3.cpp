/************************************************
Filename: Ass3.cpp
Version: 1.0
Student Name: Patrick Bobyn
Student Number: 040889706
Course Name: Numerical Computing
Course Code:CST8233
Lab Section Number: 302
Assignment Name: Assignment 3
Due Date: 2019/12/06
Submission Date:2019/11/25
Professor's Name: Abdullah Kadri
Uses the Euler ODE or the Runge-Kutta ODE for an equation.
**********************************/

#include <iostream>
#include <iomanip>

using namespace std;

void euler(double);
void runge_kutta(double);
double differential(double, double);

/***********************************************
Function name: main()
Purpose: Main method

In parameters: void
Out Parameters: int
Version: 1.0
Author: Patrick Bobyn
************************************************/


int main() {

	// local variables
	char option = ' ';
	double size = 0;

	// a do while loop until the quit option is selected
	while (option != '3') {
		cout << ">> Choose the method for solving ODE:\n1. Euler's Method\n2. Runge-Kutta 4th Order Method\n3. Quit\n>> ";
		cin >> option;

		if (option == '1' || option == '2') {
			cout << "Choose step size \"h\" (0.8, 0.2, 0.05)\n>> ";
			if (cin >> size) {}
			else if (cin.fail()) {
				cin.clear();
				cout << "Invalid Input";
				continue;
			}
		}

		switch (option) {
		case '1':	// Euler option
			euler(size);
			break;
		case '2':	// Runge-Kutta option
			runge_kutta(size);
			break;
		case '3':	// quit
			cout << "Quitting";
			break;
		default:	// default
			cout << "Invalid Option" << endl;
		}
	}
}

/***********************************************
Function name: euler()
Purpose: Runs the program to calculate the euler ode

In parameters: double
Out Parameters: void
Version: 1.0
Author: Patrick Bobyn
************************************************/

void euler(double h) {

	// local variables
	double y = 3;
	double t = 0;

	// the amount of loops
	int n = (int)(2.0 / h);

	// print out the table head
	cout << "Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%)" << endl;

	// loop through each line of table
	for (int i = 0; i < n; i++) {
		
		// get the values to be printed out
		y = y + h * differential(t, y);
		t += h;
		double exact = 0.1 * cos(4.0 * t) + 0.2 * sin(4.0 * t) + 2.9 * exp(-2.0 * t);	
		double error = 100 * fabs((y - exact) / exact);

		// print out the values
		cout << fixed << setprecision(1) << t << "\t" << setprecision(3) << exact << "\t\t" << y << "\t\t\t" << setprecision(2) << error << endl;
	}
	cout << endl;
}

/***********************************************
Function name: runge_kutta()
Purpose: Runs the runge-kutta ode.

In parameters: double
Out Parameters: void
Version: 1.0
Author: Patrick Bobyn
************************************************/


void runge_kutta(double h) {
	
	// local variables
	double rk1, rk2, rk3, rk4;
	double y = 3;
	double t = 0;

	// the amount of loops
	int n = (int)(2.0 / h);

	// print out table head 
	cout << "Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%)" << endl;

	// loop through each line of the table
	for (int i = 0; i < n; i++) {

		// get values for runge_kutta
		rk1 = h * differential(t, y);
		rk2 = h * differential(t + 0.5 * h, y + 0.5 * rk1);
		rk3 = h * differential(t + 0.5 * h, y + 0.5 * rk2);
		rk4 = h * differential(t + h, y + rk3);
		
		// get the values to be printed out
		y = y + (1.0 / 6.0) * (rk1 + 2 * rk2 + 2 * rk3 + rk4);
		t += h;
		double exact = 0.1 * cos(4 * t) + 0.2 * sin(4 * t) + 2.9 * exp(-2 * t);	
		double error = 100 * fabs((y - exact) / exact);

		// print out the values
		cout << fixed << setprecision(1) << t << "\t" << setprecision(3) << exact << "\t\t" << y << "\t\t\t" << setprecision(2) << error << endl;
	}
	cout << endl;
}

/***********************************************
Function name: differential()
Purpose: Returns the equation cos(4t)-2y

In parameters: double
Out Parameters: double
Version: 1.0
Author: Patrick Bobyn
************************************************/


double differential(double x, double y) {
	// return the equation cos(4t)-2y
	return cos(4 * x) - 2 * y;
}