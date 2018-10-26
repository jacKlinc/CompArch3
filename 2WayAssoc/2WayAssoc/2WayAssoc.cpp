/* The following is a cache simulator for a 2-Way Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 We need to compare the lower half of each address, if they match it's a hit

*/

#include "pch.h"

struct CacheEntry {
	unsigned short upprAddr; // 16 bit uppr addr
	bool validFlag; //  prevents same copy, flag is set if data valid
	bool dramDis; // DRAM disable flag
	bool LRUFlag; // Last Recently Used
	char data[4]; // 32 bit data bus
};

int main()
{
	unsigned int CPUAddr; // 32 bit CPU Addr
	unsigned short CPULwr; // lwr half anded with ffff to give lwr
	unsigned short CPUUppr; // uppr half anded with ffff then bit shifted by 16
	unsigned short setNo; // which element in way0[] 
	unsigned short byteNo; // the lower addr is anded to give
	char data; // byte of data	

	ifstream myAddr("testAddresses.txt"); // text file used
	ifstream myData("testData.txt"); // text file used
	CacheEntry way0[16384]; // 2^14 cache entries
	CacheEntry way1[16384]; // second direct mapped cache
	string index1, index2;

	if (myAddr.is_open()) {//if the file is open
		while (!myAddr.eof()) { //while the end of file is NOT reached
			myAddr >> hex >> CPUAddr;
			CPULwr = CPUAddr & 0x0000ffff; // lwr half anded with ffff to give lwr
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // uppr half anded with ffff then bit shifted by 16
			setNo = (CPULwr & 0xfffc) >> 2; // which element in way 
			byteNo = CPULwr & 3; // the lower addr is anded to give

			if (CPUUppr == way0[setNo].upprAddr) { // Hit
				data = way0[setNo].data[byteNo];
				cout << "Hit \n";
			}
			else if (CPUUppr == way1[setNo].upprAddr) { // Hit in second direct mapped cache
				data = way1[setNo].data[byteNo];
				cout << "Hit \n";
			}
			else {
				cout << "Miss \n";
				way0[setNo].validFlag, way1[setNo].validFlag = 0;
			}
			CPUUppr = way1[setNo - 1].upprAddr;
		}
		myAddr.close(); //closing the file
	}
	else cout << "Unable to open file \n"; //if the file is not open output
}