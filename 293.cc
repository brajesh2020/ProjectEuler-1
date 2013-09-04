#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (1000000008)
#define PRIME_COUNT (50847535)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};
long long max_gap = 1;

void Sieve()
{
    long long curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            primes[curr_pos] = i;
            if (curr_pos > 0 && primes[curr_pos] - primes[curr_pos - 1] > max_gap)
            {
                max_gap = primes[curr_pos] - primes[curr_pos - 1];
            }
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
    std::cout << "max_gap => " << max_gap << std::endl;
}

bool IsAdmissibleNumber(long long n)
{
    long long d = n;
    for (long long i = 0; i < PRIME_COUNT; i++)
    {
        if (d % primes[i] != 0)
        {
            return false;
        }
        while (d % primes[i] == 0)
        {
            d /= primes[i];
        }
        if (d == 1)
        {
            break;
        }
    }
    return true;
}

bool IsPseudoFortunateNumbers(long long n)
{
    long long t;
    for (long long i = 1; i < PRIME_COUNT; i++)
    {
        t = primes[i] - n;
        if (t > primes[i-1] && IsAdmissibleNumber(t))
        {
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    Sieve();
    long long sum = 0;
    for (long long m = 3; m <= max_gap; m += 2)
    {
        if (IsPseudoFortunateNumbers(m))
        {
            sum += m;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
