/*
Lab1_Flops.cpp : This file contains the 'main' function. Program execution begins and ends there.

This script determines the computers ability to complete operations based on data type, 
from short int (2B), long int (4B), float (4B), and double (8B).
*/
#include "pch.h"

int main()
{
	int x = 10;
	int y = 3;
	long int longx = 9;
	long int longy = 2;
	float floatx = 9.2;
	float floaty = 3.6;
	double doublex = 2.63;
	double doubley = 6.8;
	
	int loopCount = 0;
	double elapsedTime;

	// Short Int
	clock_t start = clock();
	do{
		for (int i = 0; i < 40000; i++) {
			x = x + y;
		}
		loopCount++;
	} while (elapsedTime = ((clock() - start)/(double)CLOCKS_PER_SEC) < 5); 
	// (time at end of loop - time at start of loop)/clocks per second as a double
	cout << "Number of short integers: \n" << loopCount;

	// Long
	start = clock();
	do {
		for (int i = 0; i < 40000; i++) {
			longx = longx + longy;
		}
		loopCount++;
	} while (elapsedTime = ((clock() - start) / (double)CLOCKS_PER_SEC) < 5);
	cout << "\nNumber of long integers: \n" << loopCount;

	// Float
	start = clock();
	do {
		for (int i = 0; i < 40000; i++) {
			floatx = floatx + y;
		}
		loopCount++;
	} while (elapsedTime = ((clock() - start) / (double)CLOCKS_PER_SEC) < 5);
	cout << "\nNumber of floats: \n" << loopCount;

	// Double
	start = clock();
	do {
		for (int i = 0; i < 40000; i++) {
			doublex = doublex + y;
		}
		loopCount++;
	} while (elapsedTime = ((clock() - start) / (double)CLOCKS_PER_SEC) < 5);
	cout << "\nNumber of doubles: \n" << loopCount;
}
