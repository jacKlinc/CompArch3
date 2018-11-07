/* The following is a cache simulator for a 2-Way Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 Computer Architecture 3 Formal Element

 Jack Harding
*/

#include "pch.h"
using namespace std;

struct cacheEntry {
	unsigned short upperAddr;	// creating variable for upper address
	bool validFlag;				// valdid flag indicates wether or not cache entry is valid
	bool LRUFlag;				// least recently used flag indicates if the cache entry was the last to be used
	char data[4];				// array for storing data
};

cacheEntry way0[16384], way1[16384]; 
string addrS;

ifstream myAddr("testAddresses.txt");// reading in file with adresses
unsigned int CPUAddr;
unsigned char byteNo;
unsigned short CPUUppr, setNo, hits = 0, misses = 0;

int main()
{
	for (int i = 0; i <= 16384; i++) { // initialising flags before adress are sent
		way0[i].validFlag = 0;		// valid fag initialised to zero on startup
		way0[i].LRUFlag = 1;		// setting LRU flag in way0 to be 1 as I want the program to store adresses in way0 first
		way1[i].validFlag = 0;		// valid fag initialised to zero on startup
		way1[i].LRUFlag = 0;		//setting LRU flag in way1 to be 0 as I want the program to store adresses in way1 second

	}

	cout << "2-Way Set Associative Cache Simulator \n\n";

	if (myAddr.is_open()) {
		while (getline(myAddr, addrS)) {
			stringstream tempS(addrS);				// reading in first line of address file
			tempS >> hex >> CPUAddr;				// converting first line to hex
			CPUUppr = (CPUAddr & 0xffff0000) >> 16;	// bit shifting by 16 and and'ing CPU address with 0xffff0000 to get upper part of CPU address
			setNo = (CPUAddr & 0x0000fffc) >> 2;	// bit shifting by 2 and and'ing CPU address with 0x0000ffff to get setNo part of CPU address
			byteNo = CPUAddr & 3;					// and'ing CPU address with 3 to isolate the last two bits which will get the requested byte number

			if ((way0[setNo].upperAddr == CPUUppr) && (way0[setNo].validFlag == 1)) {// only getting a hit if upper adress in CPU address matches upper adress stored in
				cout << "Full Addr: 0x" << hex << CPUAddr;
				cout << "     Hit:   0x" << hex << CPUUppr << "   way0" << endl;
				hits ++; // incrementing hit count
				way0[setNo].LRUFlag = 0;   //MOST Recently Used, changing way0 to most recently used
				way1[setNo].LRUFlag = 1;   // changing way1 to least recently used
			}

			else if ((way1[setNo].upperAddr == CPUUppr) && (way1[setNo].validFlag == 1)) { // only getting a hit if upper adress in CPU address matches upper adress stored i 
				cout << "Full Addr: 0x" << hex << CPUAddr;
				cout << "     Hit:   0x" << hex << CPUUppr << "   way1" << endl;
				hits ++;		// incrementing hit count
				way1[setNo].LRUFlag = 0;   //MOST Recently Used, changing way1 to most recently used
				way0[setNo].LRUFlag = 1;   // changing way1 to least recently used
			}

			else // if a hit ddn't occur a miss had to have occured
			{

				if (way0[setNo].LRUFlag == 1) {			// enter if way0 is LRU
					cout << "Full Addr: 0x" << hex << CPUAddr; // tidies output
					cout << "     Miss:  0x" << hex << CPUUppr << "   way0" << endl;
					way0[setNo].upperAddr = CPUUppr;	// sets the upper address in way0[setNo] to CPUUppr
					way0[setNo].validFlag = 1;			// entry is valid
					way0[setNo].LRUFlag = 0;			// way0 to most recently used
					way1[setNo].LRUFlag = 1;			// way1 to least recently used
					misses ++;							// miss
				}

				else {									// enter when way1 is LRU
					cout << "Full Addr: 0x" << hex << CPUAddr;
					cout << "     Miss:  0x" << hex << CPUUppr << "   way1" << endl;
					way1[setNo].upperAddr = CPUUppr;	// sets the upper address in way1[setNo] to CPUUppr
					way1[setNo].validFlag = 1;			// entry is valid
					way1[setNo].LRUFlag = 0;			// way1 to most recently used
					way0[setNo].LRUFlag = 1;			// way0 to least recently used
					misses ++;
				}
			}
		}
		myAddr.close(); // closes file
	}
	else
		cout << "Unable to openfile"; // prints error message in case file can't be opened

	cout << "\nTotal Hits:   " << dec << hits << endl;
	cout << "Total Misses: " << dec << misses << endl;

	system("pause");
	return 0;
}