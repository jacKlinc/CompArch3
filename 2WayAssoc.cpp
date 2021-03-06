/* The following is a cache simulator for a 2-Way Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 We need to compare the lower half of each address, if they match it's a hit

*/

#include "pch.h"

struct CacheEntry {
	unsigned short upprAddr;	// 16 bit uppr addr
	bool validFlag;				// prevents same copy, flag is set if data valid
	bool LRUFlag;				// Last Recently Used
	char data[4];				// 32 bit data bus
};

unsigned int CPUAddr;		// 32 bit CPU Addr
unsigned short CPULwr;		// lwr half anded with ffff to give lwr
unsigned short CPUUppr;		// uppr half anded with ffff then bit shifted by 16
unsigned short setNo;		// which element in way0[] 
unsigned short byteNo;		// the lower addr is anded to give
unsigned short hits = 0, misses = 0;
bool up, val, up1, val1;

ifstream myAddr("testAddresses.txt"); // text file used
CacheEntry way0[16384], way1[16384]; // 2^14 cache entries, second direct mapped cache
string sAddr;

int main()
{
	for (int i = 0; i <= 16384; i++){ // initialising flags before adress are sent
		way0[i].validFlag = 0;		// valid fag initialised to zero on startup
		way0[i].LRUFlag = 1;		// setting LRU flag in way0 to be 1 as I want the program to store adresses in way0 first
		way1[i].validFlag = 0;		// for way1
		way1[i].LRUFlag = 0;		// for way1
	}

	cout << "2-Way Set Associative Cache Simulator \n \n";

	if (myAddr.is_open()) {					//if the file is open
		while (!myAddr.eof()) {				//while the end of file is NOT reached
			stringstream lineIn(sAddr);		// 1st line of address file
			myAddr >> hex >> CPUAddr;		// line treated as hex
			CPULwr = CPUAddr & 0x0000ffff;	// cpu anded with ffff to give lwr
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // uppr half anded with ffff then bit shifted by 16
			setNo = (CPUAddr & 0x0000fffc) >> 2;
			byteNo = CPULwr & 3;			// lower addr is anded with 3

			val = way0[setNo].validFlag;
			up = way0[setNo].upprAddr == CPUUppr; // tidy code
			if (up && val) {					// Hit
				cout << "Hit:    " << hex << CPUAddr << endl;
				hits++;
				way0[setNo].LRUFlag = 0; // way0 using most recently used
				way1[setNo].LRUFlag = 1; // way1 using Least Recently Used
			}
			else if (up1 && val1) {		// Hit
				cout << "Full Addr: 0x" << hex << CPUAddr;
				cout << "     Hit:  0x" << hex << CPUUppr << endl;
				hits++;
				way0[setNo].LRUFlag = 1; // way0 using LRU
				way1[setNo].LRUFlag = 0; // way1 using non-LRU
			}
			else { 	// Miss
				cout << "Miss:   " << hex << CPUAddr << endl;
				misses++;
				if (way0[setNo].LRUFlag) {
					way0[setNo].upprAddr = CPUUppr;	// sets the upper address in way0[setNo] to CPUUpper
					way0[setNo].validFlag = 1;		
					way0[setNo].LRUFlag = 0;		// Most Recently Used, changing way0 to most recently used
					way1[setNo].LRUFlag = 1;		// changing way1 to least recently used
				}
				else {
					way1[setNo].upprAddr = CPUUppr;	
					way1[setNo].validFlag = 1;			
					way1[setNo].LRUFlag = 0;			// most Recently Used, changing way0 to most recently used
					way0[setNo].LRUFlag = 1;			// changing way1 to least recently use
				}
			}
		}
		myAddr.close(); //closing the file
		cout << "Hits: " << hits << "\n Misses: " << misses << endl;
	}
	else cout << "Unable to open file \n"; //if the file is not open output
}