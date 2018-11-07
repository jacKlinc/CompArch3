// FormalElement1.cpp : Direct Mapped
// Christopher O' Connor
// 1/11/2018

#include "pch.h"

using namespace std;

struct cacheEntry{				// what will be in each cahe entry
	unsigned short upprAddr;	// creating variable for upper address
	bool validFlag;				// valdid flag indicates whether or not cache entry is valid
	bool LRUFlag;				// least recently used flag indicates if the cache entry was the last to be used
	char data[4];				// array for storing data
};

cacheEntry way0[16384]; // creating a "way" where there are 16384 cache entries

unsigned short CPUUppr, setNo; // variables to store setNo and CPUUpper
unsigned char byteNo;			// cahr variable created to to store a byte number

int main()
{
	cout << "Direct Mapped Cache Simulator\n\n";
	
	string addrString;
	unsigned int CPUAddr;				// creating int for CPU addresses
	ifstream myAddr ("testAddresses.txt");	// reading in file with adresses
	unsigned short hits = 0, misses = 0;						// setting hitcount to 0, used to track how many his occure

	for (int i = 0; i <= 16384; i++) //initialising LRU flags and validflags
	{
		way0[i].validFlag = 0; //valid flags initialised to zero any data on boot up in Tag is junk
		way0[i].LRUFlag = 1; // LRU flags initialised, although not used in the direct mapped they are still there
	}

	if (myAddr.is_open())
	{
		while (getline(myAddr, addrString))
		{
			stringstream tempS(addrString);	// reading in first line of address file
			tempS >> hex >> CPUAddr;			//convertin adress in .txt file into hex

			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // bit shifting by 16 and and'ing CPU address with 0xffff0000 to get upper part of CPU address
			setNo = (CPUAddr & 0x0000fffc) >> 2;	 // bit shifting by 2 and and'ing CPU address with 0x0000ffff to get setNo part of CPU address
			byteNo = CPUAddr & 3;					 // and'ing CPU address with 3 to isolate the last two bits which will get the requested byte number

			if ((way0[setNo].upprAddr == CPUUppr) && (way0[setNo].validFlag == 1)) //what to do if there is a hit and valid flag is 1
			{
				cout << "Full Addr: 0x" << hex << CPUAddr;
				cout << "     Hit:  0x" << hex << CPUUppr << endl;
				hits++;			// incrementing hit counter everytime a hit occurs
			}

			else // what to do if there is a miss, i.e the upper Adresses didn't match orvalid flag not equal to one
			{
				cout << "Full Addr: 0x" << hex << CPUAddr;
				cout << "     Miss: 0x" << hex << CPUUppr << endl;
				way0[setNo].upprAddr = CPUUppr;	// storing CPUUpper into location defined by setNo
				way0[setNo].validFlag = 1;			//setting vali flag to one 
				misses++;
			}
		}
		myAddr.close(); // closing file
	} 

	else //if file doesn't open corrctly the else statement displays error measagae
	{
		cout << "\nFile Open Failed\n";
	}
	//printing out number of hits and the end of the program
	cout << "\nTotal Hits:   " << dec << hits << endl;
	cout << "Total Misses: " << dec << misses << endl;
	system("pause");
	return 0;
}