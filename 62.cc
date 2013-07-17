#include <map>
#include <iostream>
#include <stdio.h>

std::map<long long, long long> reversed_hash_map;
std::map<long long, int> freq;

long long BuildFivePermutation(long long n)
{
    int digits[10] = {};
    
    long long d = n*n*n;
    while (d)
    {
        digits[d % 10]++;
        d /= 10;
    }

    long long hash = 0;
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j < digits[i]; j++)
        {
            hash *= 10;
            hash += i;
        }
    }

    freq[hash]++;
    if (freq[hash] == 1)
    {
        reversed_hash_map[hash] = n*n*n;
    }

    if (freq[hash] == 5)
    {
        return reversed_hash_map[hash];
    }
    else
    {
        return -1;
    }
}

int main(int argc, char* argv[])
{
    long long rv;
    for (long long n = 1; n < 2097152; n++)
    {
        rv = BuildFivePermutation(n);
        if (rv > 0)
        {
            std::cout << rv << std::endl;
            break;
        }
    }
    return 0;
}