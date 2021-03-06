/* The following is a cache simulator for a Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64iB data cache

 Associative cache allows for the addresses to be stored anywhere in the 
 cache, rather than a fixed location liie direct mapped. 

 Is way0/CPUUppr/lwr needed if the entire address is compared?

*/

#include "pch.h"

struct CacheEntry {
	unsigned short fAddr; // 32 bit addr
	bool validFlag; //  prevents same copy, flag is set if data valid
	bool LRUFlag; // Least Recently Used
	unsigned char data[4]; // 32 bit data bus
};

//bool isCounter(unsigned short counter);

unsigned int CPUAddr; // 32 bit CPU Addr
unsigned short CPUUppr, hits = 0, misses = 0, search = 0, counter = 0;
unsigned char byteNo;
bool isFull = 0, isHit = 0, fAdd, val; // is cache full/hit, tidy code
string addrS;
ifstream myAddr;// text file used
CacheEntry way0[16384]; // 2^14 cache entries


int main()
{	cout << "Fully Associative Cache Simulator \n\n";

	for (int i = 0; i <= 16384; i++) { // initialising flags
		way0[i].validFlag = 0;
		way0[i].LRUFlag = 1;
	}

	myAddr.open("testAddresses.txt"); 
	if (myAddr.is_open()) { //if the file is open
		while (getline(myAddr, addrS)) { //while the end of file is NOT reached
			stringstream tempS(addrS);
			tempS >> hex >> CPUAddr;
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // bit shifting 16 anded with CPU address 
			byteNo = CPUAddr & 3;
			fAdd = (way0[search].fAddr == CPUAddr);
			val = (way0[search].validFlag);

			if (!isFull) {
				while (search <= counter) {
					if ((way0[search].fAddr == CPUAddr) && (way0[search].validFlag)) {
						cout << "Hit: " << hex << CPUAddr;
						string* byteOut;
						byteOut = (string*)byteNo; // typecasting byteNo into a string for displaying
						cout << hex << byteOut << dec; // displaying which byte the CPU wants
						hits++;					// increments hit counter
						isHit = 1;				// indicates a hit
					}
					search++;					// used when cache isn't full
				}
				//isCounter(counter); // if no hits occur call this
				if (!isHit) {							// write to cache using FIFO
					if (!counter) {
						way0[counter].fAddr = CPUAddr;	// storing address
						way0[counter].validFlag = 1;	// valid flag to 1
						way0[counter].LRUFlag = 0;		// Most Recently Used
						counter++;						// counter=0, must be incremented
					}
					else {								// being used now
						for (int i = counter; i > 0; i--) { // iterating down old addr
							way0[i] = way0[i - 1];		// moving old addr to front
							way0[i].LRUFlag = 1;		// using LRU when counter>0
						}
						way0[0].fAddr = CPUAddr;		// storing recent addr first
						way0[0].validFlag = 1;
						way0[0].LRUFlag = 0;			// first element is MRU
						counter++;
						misses++;
						if (counter == 16384)
							isFull = 1;					// cache is full
					}
				}
			}
			else {										// cache is now full
				for (int i = 0; i < 16384; i++){		// all cache entries have relevant addresses
					fAdd = (way0[i].fAddr == CPUAddr);
					val = (way0[i].validFlag);
					if (fAdd && val){					// hit when addr match and valid
						hits++;
						isHit = 1;						// using isHit as flag so prog knows miss occured
					}
					else {								//miss
						for (i = 16384; i > 0; i--) {
							way0[i] = way0[i - 1];		// shifting all addr by one space
							way0[i].LRUFlag = 1;
						}
						way0[0].fAddr = CPUAddr;
						way0[0].validFlag = 1;
						way0[0].LRUFlag = 0;			// MRU
						misses++;
					}
				}
			}
		}
		cout << "\nHits: " << hits << endl;
		cout << "Misses: " << misses << endl;
		myAddr.close(); //closing the file
	} 
	else cout << "\nFile not opened";
}

/*
bool isCounter(unsigned short counter) {
	
}
*/
