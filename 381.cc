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

// -----------------------------------------------------------------------------

long long last_x, last_y;
long long x, y, t, quotient;

void ExtendedGCD(long long a, long long b)
{
    x = 0;
    y = 1;
    last_x = 1;
    last_y = 0;
    while (b)
    {
        quotient = a / b;
        t = a;
        a = b;
        b = t % b;

        t = x;
        x = last_x - quotient*x;
        last_x = t;
        
        t = y;
        y = last_y - quotient*y;
        last_y = t;
    }
}

long long GetInverse(long long a, long long prime)
{
    ExtendedGCD(a, prime);
    return last_x;
}

long long S(long long prime)
{
    long long sum = 0;
    sum -= GetInverse(2, prime);
    sum += GetInverse(6, prime);
    sum -= GetInverse(24, prime);
    sum %= prime;
    return (sum < 0) ? sum + prime : sum;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    long long total_sum = 0;
    for (int i = 2; i < PRIME_COUNT; i++)
    {
        total_sum += S(prime[i]);
    }
    std::cout << total_sum << std::endl;
    return 0;
}