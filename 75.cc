#include <iostream>
#include <stdio.h>

int visited_count[1500001] = {};

long long GetGCD(long long a, long long b) 
{
    while (b) 
    {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

void InitVisitedCountTable()
{
    long long triple_sum;
    for (long long m = 2; m*m < 1500000; m++)
    {
        for (long long n = 1; n < m && 2*m*(m+n) <= 1500000; n++)
        {
            if ((m-n) % 2 == 1 && GetGCD(m,n) == 1)
            {
                triple_sum = 2*m*(m+n);
                for (long long i = triple_sum; i <= 1500000; i += triple_sum)
                {
                    visited_count[i]++;
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitVisitedCountTable();

    int count = 0;
    for (long long L = 1; L <= 1500000; L++)
    {
        if (visited_count[L] == 1)
        {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}