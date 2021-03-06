/*
*****************************************************
Computer Architecture 3 Formal Element Cache Simulator

 Direct Mapped Cache
 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 Written in VS Studio 2017 by Jack Harding
 08/11/2018
*****************************************************
*/

#include "pch.h"

struct CacheEntry {
	unsigned short upprAddr;											// 16-bit tag addr
	bool validFlag;														//  prevents copy, flag is set if data valid
	bool LRUFlag;														// Least Recently Used eviction policy
	char data[4];														// 32-bit data bus
};

unsigned short ;
unsigned short CPUUppr, CPULwr, byteNo, setNo, hits = 0, misses = 0;													// uppr half anded with ffff then bit shifted by 16
// which element in way0[] 
unsigned int CPUAddr;													// 32 bit CPU Addr
unsigned short ;													// lwr half anded with ffff to give lwr
unsigned char ;													// the lower addr is anded to give

ifstream myAddr("testAddresses.txt"); // addr text file used
CacheEntry way0[16384]; // 2^14 cache entries
string sAddr; // used to store line 

int main()
{
	cout << "Direct Mapped Cache Simulator: \n\n";

	

	for (int i = 0; i <= 16384; i++) {
		way0[i].validFlag = 0; //valid flags initialised to zero any data on boot up in Tag is junk
		way0[i].LRUFlag = 1; // LRU initialised, not used in the direct mapped
	}

	if (myAddr.is_open()) { //if the file is open
		while (getline(myAddr, sAddr)) { //while the end of file is NOT reached
			stringstream lineIn(sAddr); // 1st line of address file
			myAddr >> hex >> CPUAddr; // line treated as hex
			CPULwr = CPUAddr & 0x0000ffff; // cpu anded with ffff to give lwr
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // uppr half anded with ffff then bit shifted by 16
			setNo = (CPUAddr & 0x0000fffc) >> 2;
			byteNo = CPULwr & 3; // the lower addr is anded to give

			if (way0[setNo].upprAddr == CPUUppr && way0[setNo].validFlag) { // Hit
				cout << "Hit:    " << hex << CPUAddr << endl;
				hits++;
			}
			else { 	// Miss
				cout << "Miss:   " << hex << CPUAddr << endl;
				misses++;
			}
		}
		cout << "\nHits:   " << hits << endl; // counts the number of hits
		cout << "Misses: " << misses << endl; // number of misses
		myAddr.close(); //closing the file
	} else cout << "Unable to open file"; //if the file is not open output
}