#include <iostream>
#include <stdio.h>

int prime[100000000] = {};

void InitPrimeTable()
{
    for (long long i = 2; i < 100000000; i++)
    {
        if (prime[i] == 0)
        {
            prime[i] = 1;
            for (long long j = i + i; j < 100000000; j += i)
            {
                prime[j]++;
            }
            if (i < 10000)
            {
                for (long long j = i*i; j < 100000000; j += i*i)
                {
                    prime[j]++;
                }
            }
            if (i < 465)
            {
                for (long long j = i*i*i; j < 100000000; j += i*i*i)
                {
                    prime[j]++;
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    long long count = 0;
    for (long long i = 4; i < 100000000; i++)
    {
        if (prime[i] == 2)
        {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
