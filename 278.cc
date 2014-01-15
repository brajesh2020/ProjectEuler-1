#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (5000)
#define PRIME_COUNT (669)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

void Sieve()
{
    sieve_visited[0] = sieve_visited[1] = true;
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            primes[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
    std::cout << "Prime count: " << curr_pos << std::endl;
}

long long GetLargestImpossibleValue(long long p, long long q, long long r)
{
    return 2*p*q*r - p*q - q*r - r*p;
}

void Solve()
{
    long long sum = 0;
    for (long long i = 0; i < PRIME_COUNT; i++)
    {
        for (long long j = i+1; j < PRIME_COUNT; j++)
        {
            for (long long k = j+1; k < PRIME_COUNT; k++)
            {
                sum += GetLargestImpossibleValue(primes[i], primes[j], primes[k]);
            }
        }
    }
    std::cout << "Sum: " << sum << std::endl;
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
