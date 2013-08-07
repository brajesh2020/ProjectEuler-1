#include <iostream>
#include <set>
#include <stdio.h>

#define SIEVE_RANGE (40000)
#define FALSE_PRIME_RANGE (40000)
#define PRIME_COUNT (4203)

bool visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {}; 

void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

long long A(long long n)
{
    long long k = 1;
    long long r = 1;
    do 
    {
        r = (r * 10 + 1) % n;
        k++;
    }
    while (r);
    return k;
}

std::set<long long> false_primes;

void InitFalsePrimeSet()
{
    long long n;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        if (prime[i] == 2 || prime[i] == 5)
        {
            continue;
        }
        for (int j = i+1; j < PRIME_COUNT; j++)
        {
            if (prime[j] == 2 || prime[j] == 5)
            {
                continue;
            }
            n = prime[i] * prime[j];
            if (n > FALSE_PRIME_RANGE)
            {
                break;
            }
            if ((n-1) % A(n) == 0)
            {
                false_primes.insert(n);
            }
            for (int k = j+1; k < PRIME_COUNT; k++)
            {
                if (prime[k] == 2 || prime[k] == 5)
                {
                    continue;
                }
                n = prime[i] * prime[j] * prime[k];
                if (n > FALSE_PRIME_RANGE)
                {
                    break;
                }
                if ((n-1) % A(n) == 0)
                {
                    false_primes.insert(n);
                }
            }
        }
    }
}

void Solve()
{
    long long sum = 0;
    long long counter = 0;
    for (std::set<long long>::iterator it = false_primes.begin();
        it != false_primes.end(); it++)
    {
        counter++;
        if (counter > 25)
        {
            break;
        }
        sum += (*it);
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitFalsePrimeSet();
    Solve();
    return 0;
}