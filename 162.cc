#include <iostream>
#include <stdio.h>

#define DIGIT_COUNT (16)

long long counting[DIGIT_COUNT][(1 << 16) + 1] = {};

void InitCountingTable()
{
    for (int digit = 0; digit < 16; digit++)
    {
        counting[0][1 << digit] = 1;
    }

    for (int i = 1; i < DIGIT_COUNT; i++)
    {
        for (int digit = 0; digit < 16; digit++)
        {
            for (int j = 0; j < (1 << 16) + 1; j++)
            {
                counting[i][j | (1 << digit)] += counting[i-1][j];
            }
        }
    }
}

int GetOneBitCount(unsigned int n)
{
    int count = 0;
    for(count = 0; n != 0; n >>= 1L)
    {    
        if(n & 0x01)
        {
            count++;
        }
    }    
    return count;
}

int main(int argc, char* argv[])
{
    InitCountingTable();
    long long rv = 0;
    for (int i = 0; i < DIGIT_COUNT; i++)
    {
        for (int j = 1; j <= (1 << 16); j++)
        {
            if (counting[i][j] && 
                (j & (1 << 0)) && (j & (1 << 1)) && (j & (1 << 2)))
            {
                int one_bit_count = GetOneBitCount(j);
                rv += counting[i][j] / one_bit_count * (one_bit_count - 1);
            }
        } 
    }
    std::cout << std::hex << std::uppercase << rv << std::endl;
    return 0;
}