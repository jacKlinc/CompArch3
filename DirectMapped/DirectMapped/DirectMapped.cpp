/* The following is a cache simulator for a Direct Mapped Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 We need to compare the lower half of each address, if they match it's a hit

 Written in VS Studio 2017 by Jack Harding for Computer Architecture 3 Formal Element Cache 
 Simulator Report. 
*/

#include "pch.h"

struct CacheEntry {
	unsigned short upprAddr; // 16 bit uppr addr
	bool validFlag; //  prevents same copy, flag is set if data valid
	bool LRUFlag; // Least Recently Used
	char data[4]; // 32 bit data bus
};

int main()
{
	unsigned int CPUAddr; // 32 bit CPU Addr
	unsigned short CPULwr; // lwr half anded with ffff to give lwr
	unsigned short CPUUppr; // uppr half anded with ffff then bit shifted by 16
	unsigned short setNo; // which element in way0[] 
	unsigned short byteNo; // the lower addr is anded to give
	unsigned int hits = 0, misses = 0;
	char data; // byte of data	

	ifstream myAddr("testAddresses.txt"); // addr text file used
	ifstream myData("testData.txt"); // data text file used
	CacheEntry way0[16384]; // 2^14 cache entries
	string index; // used to store line 

	if (myAddr.is_open()) { //if the file is open
while (!myAddr.eof()) { //while the end of file is NOT reached
	myAddr >> hex >> CPUAddr ; // line treated as hex
	CPULwr = CPUAddr & 0x0000ffff; // lwr half anded with ffff to give lwr
	CPUUppr = (CPUAddr & 0xffff0000) >> 16; // uppr half anded with ffff then bit shifted by 16
	setNo = (CPULwr & 0xfffc) >> 2; // which element in way0[] 
	byteNo = CPULwr & 3; // the lower addr is anded to give

	if (CPUUppr == way0[setNo].upprAddr ) { // Hit
		cout << "Hit" << endl;
		hits++; // increments counter
	}
	else { 	// Miss
		cout << "Miss" << endl;
		misses++;
	}
}
cout << "Hits: " << hits << endl; // counts the number of hits
cout << "Misses: " << misses << endl; // number of misses
myAddr.close(); //closing the file
	} else cout << "Unable to open file"; //if the file is not open output
}