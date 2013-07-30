#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (100000001)
#define PRIME_COUNT (5761455)

bool sieve[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {};

inline void InitPrimeTable()
{
    sieve[0] = sieve[1] = true;
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve[j] = true;
            }
        }
    }
}

bool IsPrimeGeneratingInteger(long long n)
{
    for (long long d = 2; d*d <= n; d++)
    {
        if (n % d == 0 && sieve[d + n/d])
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    InitPrimeTable();
    
    long long sum = 0;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        if (IsPrimeGeneratingInteger(prime[i]-1))
        {
            sum = sum + prime[i] - 1;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}