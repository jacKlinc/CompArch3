bool cacheSim(unsigned int addr, int cash[3][100000] int &block_counter, int index_addr, int tag_addr)
{
    int shift_offset=log2(block_size);
    bool detected=false;
    bool misses_flag=true;

else if (cash_type==2)        // fully associative **************************************
{
    if (block_counter < number_of_blocks)
    {
        for (int i=0; i < number_of_blocks; i++)
        {
            if (cash[0][i]==addr >> shift_offset)
            {
                detected=true;
                cash[1][i]=block_counter;
                block_counter--;
                return detected; //hit
            }
        }
        
        if (!detected)
        {
            compulsry_misses++;
            cash[0][block_counter]=addr>>shift_offset;
            cash[1][block_counter]=block_counter;
            return false;  //miss
        }
    }
    else  // block counter is more than block size
    {
        //check for existence
        for (int i=0; i < number_of_blocks; i++)
        {
            if (cash[0][i]==(addr >> shift_offset))
            {
                detected=true;
                cash[1][i]=block_counter;
                //block_counter--;
                return detected; //hit
            }
        }
        
        if (!detected)
        {
            int compare=0;
            for (int i=1; i < number_of_blocks; i++)
            {
                if (cash[1][compare] > cash[1][i])
                    compare=i;
            }
            cash[0][compare]=addr >> shift_offset;
            cash[1][compare]=block_counter;
            capcity_misses++;
            return false; //miss

        }
    }
}   // end of LRU
    
}  // end of Fully associative

// Main
int looper=1000000, addr, flag, shift;

    cout << "Please, enter 0 for Direct mapped, 1 for set associative, 2 for fully associative: " << endl;
    cin >> cash_type;
    cout << "Please, enter the size of the block as a Power of 2 between 4 and 128 byte  :" << endl;
    cin >> block_size;
    cout << "Please, enter cache size: 1KB – 64KB; in steps that are power of 2: " << endl;
    cin >> cash_size;
    
    

    int cash[3][100000];
    int block_counter=0;
    int hit_counter=0;
    int index_addr=0, tag_addr=0;
    
else if (cash_type==2)  //  Fully associative**************
    {
        number_of_blocks= (cash_size*1024)/block_size;
        
        for (int i=0; i < 2; i++)   // setting all the cash with -1
            for (int j=0; j < number_of_blocks; j++)
                cash[i][j]=-10;
        
        for(int i=0; i <looper ;i++)    {
            addr = memGen4();
            flag = cacheSim(addr, cash,  block_counter, index_addr, tag_addr);          
            if (msg[flag]=="Hit")
                hit_counter++;
            block_counter++;
        }
        
        cout << "Hits  " << hit_counter<<endl << "Compulsry:  " << compulsry_misses <<endl<< "Capcity:  " << capcity_misses <<endl<< "Conflict:  " << conflict_misses <<  endl;
        
    } // end of fully associative main