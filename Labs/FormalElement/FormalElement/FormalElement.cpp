// FormalElement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "FormalElement.h"
#include <fstream>

struct CacheEntry {
	unsigned short upperAddr;
	bool validFlag; // 
	bool LRUFlag; // Last Recently Used
	char data[4]; // 32 bit data bus
};

int main()
{
	ofstream myFile;
	myFile.open("wow.txt");
	struct CacheEntry way0[16384];
	unsigned int cPUAddr = 0;
	
	unsigned short cPULower = cPUAddr & 0x0000ffff;
	unsigned short cPUUpper = (cPUAddr & 0xffff0000) >> 16;
	unsigned short setNo = (cPULower & 0xfffc) >> 2;
	unsigned short byteNo = cPULower & 3;
	if (cPUUpper == way0[setNo].upperAddr) {
		way0[setNo].data[byteNo];
	}

	int x;
	for (int i = 0; i < 50; i++) {
		x = rand() & 0xff;
		x |= (rand() & 0xff) << 8;
		x |= (rand() & 0xff) << 16;
		x |= (rand() & 0xff) << 24;
		myFile << x;
		myFile << "\n";
		myFile.close();
	}
}