/************************************************
Filename: assign1.c
Version: 1.0
Student Name: Patrick Bobyn
Student Number: 040889706
Course Name: Numerical Computing
Course Code:CST8233
Lab Section Number: 302
Assignment Name: Assignment 1: Building Motion Simulator
Due Date: 2019/09/27
Submission Date:2019/09/26
Professor's Name: Abdullah Kadri
This program calculates the Maclaurin series for the function e^(-t)*cos(t). It takes in a few user paramters and
runs the equations based off of the uesr input.
**********************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

// method declarations
void maclaurin(int, float);

/***********************************************
Function name: main
Purpose: main function

In parameters: None
Out Parameters: 0 for Success
Version: 1.0
Author: Patrick Bobyn
************************************************/

int main() {

	// Variable declarations
	char option = ' ', n;
	int terms;
	float range;

	// print title
	printf("Evaluate the Maclaurin Series approximation to exp(-1)*cos(t)\n\n");

	do { // do ... while to print out a continuous menu

		// print menu and get user option
		option = ' ';
		printf("1: Evaluate the series\n2: quit\n");
		while (scanf("%c", &option) == 0) {
			printf("Invalid answer, try again: ");
			n = getchar;
		}
		n = getchar();

		// switch ... case to do users choice
		switch (option) {
		case '1': // run the maclaurin series
			// get the number of terms
			printf("Evaluating the series\nPlease Enter the number of terms in the series (max 5 terms): ");
			while (scanf("%d", &terms) != 1 || terms < 0 || terms > 5) {
				n = getchar();
				printf("Invalid, Enter a valid number: ");
			}
			n = getchar();

			// get the range
			printf("Please enter the range of t to evaluate in 10 incrememnts (0.0 < t < +2.0): ");
			while (scanf("%f", &range) != 1 || range < 0 || range > 2) {
				n = getchar();
				printf("Invalid, Enter a valid range: ");
			}
			n = getchar();
			
			// call function maclaurin
			maclaurin(terms, range);

			break;
		case '2': // Quit the application
			printf("Quitting\n");
			break;
		default: // default setting, user didnt pick a valid option
			printf("Invalid Option! Try Again!\n\n");
			break;
		}
	} while (option != '2');

	return 0;
}

/***********************************************
Function name: maclaurin
Purpose: runs the maclaurin series

In parameters: int terms, float range
Out Parameters: nothing
Version: 1.0
Author: Patrick Bobyn
************************************************/

void maclaurin(int terms, float range) {

	// declare variables
	float increment = range / 10;
	float t = 0, series, exact, error, trunc, terror;
	int i;

	// print out display
	printf("\nMACLAURIN SERIES\n\n\tt\tSeries\t\tExact\t\tExact Error\tTrunc. Error\n");

	for (i = 0; i <= 10; i++) {

		// reset variables
		series = 1;
		trunc = 1;

		// print out t
		printf("%e\t", t);

		// Series value
		switch (terms) {
		case 1: // 1 term		series = 1							trunc = -t
			series = 1;
			trunc = (-t);
			break;
		case 2: // 2 terms		series = 1 - t						trunc = t^3/3
			series = 1 - t;
			trunc = (t * t * t) / 3;
			break;
		case 3: // 3 terms		series = 1 - t + t^3/3				trunc = -(t^4)/6
			series = 1 - t + (t * t * t) / 3;
			trunc = -(t * t * t * t) / 6;
			break;
		case 4: // 4 terms		series = 1 - t + t^3/3 - (t^4)/6	trunc = t^5/30
			series = 1 - t + (t * t * t) / 3 - (t * t * t * t) / 6;
			trunc = (t * t * t * t * t) / 30;
			break;
		case 5: // 5 terms		series = 1 -t + t^3/3 - (t^4)/6 + t^5/30	trunc = -(t^7)/630
			series = 1 - t + (t * t * t) / 3 - (t * t * t * t) / 6 + (t * t * t * t * t) / 30;
			trunc = -(t * t * t * t * t * t * t) / 630;
			break;
		}
		printf("%.5e\t", series);	// print out the value of the sereis
		
		// Exact value
		exact = (float) exp(-t) * (float)cos(t);
		printf("%.5e\t", exact);

		// Exact % Error
		error = 100 * (exact - series) / exact;
		printf("%.5e\t", error);

		// Truncated Error
		terror = 100 * trunc / series;
		printf("%.5e", terror);

		// increment t
		t += increment;

		printf("\n");
	}
	printf("\n");
}