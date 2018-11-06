/* The following is a cache simulator for a Associative Cache with
 a 32-bit CPU Addr, 8-bit data bus, 4 Byte data lines, 64kB data cache

 Associative cache allows for the addresses to be stored anywhere in the 
 cache, rather than a fixed location like direct mapped. 

 Is way0/CPUUppr/lwr needed if the entire address is compared?

*/

#include "pch.h"
#include "Associative.h"

struct CacheEntry {
	unsigned short fAddr; // 32 bit addr
	bool validFlag; //  prevents same copy, flag is set if data valid
	bool LRUFlag; // Least Recently Used
	unsigned char data[4]; // 32 bit data bus
};

bool isCounter(unsigned short myCount);

unsigned int CPUAddr; // 32 bit CPU Addr
unsigned short CPUUppr, hits = 0, misses = 0, search = 0, counter = 0;
unsigned char byteNo;
bool isFull = 0, isHit = 0;
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
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // bit shifting by 16 and and'ing CPU address with 0xffff0000 to get upper part of CPU address
			byteNo = CPUAddr & 3;

			if (!isFull) {
				while ((search <= counter) && (way0[search].fAddr == CPUAddr) && (way0[search].validFlag)) {
					cout << "Hit: " << hex << CPUAddr;
					hits++;
					isHit = 1;
					search++; // used when cache isn't full
				}
				isCounter(counter);
			}
			else {
				for (int j = 0; j < 16384; j++) // no longer using searchount as all cache entries have relevant addresses
				{
					if ((way0[j].fAddr == CPUAddr) && (way0[j].validFlag == 1)){ // hit can only occur if the  full address and the cpu adress match
						hits++;
						isHit = 1; // using isHit as a flag so that the progrm knows a miss occured
					}

					else {
						for (int k = 16384; k > 0; k--) {
							way0[k] = way0[k - 1]; //shifting all adresses by one address space
							way0[k].LRUFlag = 1;
						}
						way0[0].fAddr = CPUAddr;
						way0[0].validFlag = 1;
						way0[0].LRUFlag = 0;   //MOST Recently Use
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

bool isCounter(unsigned short myCount) {
	if (myCount == 0) {
		way0[myCount].fAddr = CPUAddr; // storing address
		way0[myCount].validFlag = 1; //  valid flag to 1
		way0[myCount].LRUFlag = 0;   //MOST Recently Used
		counter++;
	}
	else {
		for (int i = myCount; i > 0; i--) { // iterating down old addresses
			way0[i] = way0[i - 1]; // moving old addresses to front
			way0[i].LRUFlag = 1;
		}
		way0[0].fAddr = CPUAddr;
		way0[0].validFlag = 1;
		way0[0].LRUFlag = 1;
		counter++;
		misses++;
		if (myCount == 16384)
			isFull = 1;
	}
}
