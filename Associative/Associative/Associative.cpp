/* The following is a cache simulator for a Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 Associative cache allows for the addresses to be stored anywhere in the 
 cache, rather than a fixed location like direct mapped. 

 Is way0/CPUUppr/lwr needed if the entire address is compared?

*/

#include "pch.h"

struct CacheEntry {
	unsigned short upprAddr; // 16 bit uppr addr
	bool validFlag; //  prevents same copy, flag is set if data valid
	bool LRUFlag; // Last Recently Used
	unsigned char data[4]; // 32 bit data bus
};

int main()
{
	unsigned int CPUAddr; // 32 bit CPU Addr
	unsigned short CPULwr; // lwr half anded with ffff to give lwr
	unsigned short CPUUppr; // uppr half anded with ffff then bit shifted by 16
	unsigned short setNo; // which element in way0[] 
	unsigned short byteNo; // the lower addr is anded to give
	const unsigned short cacheSize = 16;
	char dataRx;

	ifstream myAddr;// text file used
	ifstream myData; // text file used
	CacheEntry way0[16384]; // 2^14 cache entries
	string index;

	//myData.open("testData.txt");
	myAddr.open("testAddresses.txt"); 
	if (myAddr.is_open()) { //if the file is open
		while (!myAddr.eof()) { //while the end of file is NOT reached
			myAddr >> hex >> CPUAddr;
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // uppr half anded with ffff then bit shifted by 16
			byteNo = CPULwr & 3; // the lower addr is anded to give

			for (int i = 0; i < cacheSize; i++) { // Cache Check
				if (way0[i].upprAddr == CPUUppr){
					way0[i].validFlag = true;
					// data = way0[setNo].data[byteNo];
					cout << "Hit \n";
				} 
				else {
					cout << "Miss \n";
					way0[i].validFlag = false;
				}
			} 
		} myAddr.close(); //closing the file
	} 
	else cout << "File not opened \n";
}