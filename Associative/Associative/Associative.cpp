// FormalElement3.cpp Associative
// Christopher O' Connor
// 2/11/2018

#include "pch.h"

struct cacheEntry {
	unsigned int FullAddr;
	bool ValidFlag; // valid flag indicating entry is valid
	bool LRUFlag;   //least recently used
	char data[4];
};

cacheEntry way0[16384];

unsigned short CPUUppr;
unsigned char byteNo;
int hitDetect = 0, hits = 0, searchCount = 0, counter = 0, fullUp=0, misses=0;

int main()
{
	
	string addrString;
	unsigned int CPUAddr;
	ifstream Input("testAddresses.txt");

	cout << "Fully Associative Cache Simulator\n\n";

	for (int i = 0; i <= 16384; i++){ // initialising flags
		way0[i].ValidFlag = 0;
		way0[i].LRUFlag = 1;
	}

	if (Input.is_open()){
		while (getline(Input, addrString))		{
			stringstream blah(addrString);
			blah >> hex >> CPUAddr;
			CPUUppr = (CPUAddr & 0xffff0000) >> 16; // bit shifting by 16 and and'ing CPU address with 0xffff0000 to get upper part of CPU address
			byteNo = CPUAddr & 3;
			searchCount = 0; 
			hitDetect = 0; // used this to detect if a hit occured
			//cout << "Full Addr: 0x" << hex << CPUAddr;

			if (fullUp == 0) {
				while (searchCount <= counter)	{
					if ((way0[searchCount].FullAddr == CPUAddr) && (way0[searchCount].ValidFlag == 1)) // hit can only occur if the  full address and the cpu adress match
					{
						cout << "Full Addr: 0x" << hex << CPUAddr;
						cout << "     Hit:  0x" << hex << CPUUppr << endl;
						hits = hits + 1; // incrementing hit count
						hitDetect = 1; // using hitDetect as a flag so that the progrm knows that no hits were found and a miss occured
					}
					searchCount = searchCount + 1;
				}
				// setting up writing to cache, operates on FIFO system
				if (hitDetect == 0){ // only works if there were no hits
					if (counter == 0) // used for the instance when an address needs to be stored in the first location
					{
						way0[counter].FullAddr = CPUAddr; // storing the address
						way0[counter].ValidFlag = 1; // setting valid flag to 1
						way0[counter].LRUFlag = 0;   //MOST Recently Use, not particularly need but it is there
						counter = counter + 1; // inrementing counter to account for last location used for storage
					}

					else if (0 < counter <= 16384) {// used in the instance 
						for (int i = counter;i > 0; i--) // iterating through old addresses
						{
							way0[i] = way0[i - 1]; // moving old addresses forward
							way0[i].LRUFlag = 1;
						}
						way0[0].FullAddr = CPUAddr; // storing most recent address into first slot
						way0[0].ValidFlag = 1;		//setting valid flag to 1
						way0[0].LRUFlag = 0;		//MOST Recently Use
						cout << "Full Addr: 0x" << hex << CPUAddr;
						cout << "     Miss: 0x" << hex << CPUUppr << endl;
						counter = counter + 1;		// incrementing Counter
						misses = misses + 1;
						if (counter == 16384)
						{
							fullUp = 1; // indicates if the associative cache has stored the most CPU addresses it can without replacing them
						}
					}
				}
			}

			else { // cache has now stored the most amount of CPU addresses that it can with replacing others
				for (int i = 0; i < 16384; i++) // no longer using searchount as all cache entries have relevant addresses
				{
					if ((way0[i].FullAddr == CPUAddr) && (way0[i].ValidFlag == 1)) // hit can only occur if the  full address and the cpu adress match
					{
						cout << "Full Addr: 0x" << hex << CPUAddr;
						cout << "     Hit:  0x" << hex << CPUUppr << endl;
						hits = hits + 1; // incrementing hit count
						hitDetect = 1; // using hitDetect as a flag so that the progrm knows that no hits were found and a miss occured
					}

					else if (hitDetect == 0)
					{
						for (int i = 16384;i > 0; i--)
						{
							way0[i] = way0[i - 1]; //shifting all adresses by one address space
							way0[i].LRUFlag = 1;
						}
						way0[0].FullAddr = CPUAddr;
						way0[0].ValidFlag = 1;
						way0[0].LRUFlag = 0;   //MOST Recently Use
						cout << "Full Addr: 0x" << hex << CPUAddr;
						cout << "Miss: 0x" << hex << CPUUppr << endl;
						misses = misses + 1;
					}
				}
			}
			//cout << "        " << hits << "             " << misses << "\n";
		}
		Input.close();
	}

	else
	{
		cout << "Unable to openfile";
	}

	cout << "\nTotal Hits:   " << dec << hits << endl;
	cout << "Total Misses: " << dec << misses << endl;

	system("pause");
	return 0;
}

