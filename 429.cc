#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (100000001)
#define PRIME_COUNT (5761455)
#define MOD (1000000009)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};
long long prime_factors[PRIME_COUNT] = {};

void Sieve() 
{
    sieve_visited[0] = sieve_visited[1] = true;
    int pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!sieve_visited[i])
        {
            primes[pos] = i;
            long long power = i;
            while (power < SIEVE_RANGE)
            {
                for (long long j = power; j < SIEVE_RANGE; j += power)
                {
                    prime_factors[pos]++;
                    sieve_visited[j] = true;
                }
                power *= i;
            }
            pos++;
        }
    }
}

long long ModPow(long long a, long long n, long long mod)
{
    long long rv = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1)
        {
            rv *= a;
            rv %= mod;
        }
        a *= a;
        a %= mod;
    }
    return rv % mod;
}

void Solve() 
{
    long long rv = 1;
    for (long long i = 0; i < PRIME_COUNT; i++)
    {
        rv *= (1LL + ModPow(primes[i], prime_factors[i]*2, MOD));
        rv %= MOD;
    }   
    std::cout << rv << std::endl;
}

int main(int argc, char* argv[]) 
{
    Sieve();
    Solve();
    return 0;
}