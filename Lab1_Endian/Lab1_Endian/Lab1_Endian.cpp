/* 
Lab1_Endian.cpp : This file contains the 'main' function. Program execution begins and ends there.
This script checks if a PC is little/big endian
*/

#include "pch.h"

int main()
{
	char *y; // makes a pointer
	int x = 12;
	y = (char*)&x; // typecast 
	if (*y == 12) // checks if 12 is stored at the start
		cout << "\n MCU is little endian";
	else // and if not it must be stored at the end (big endian)
		cout << "\n MCU is big endian";
}