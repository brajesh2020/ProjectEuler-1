#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (1000000)
#define PRIME_COUNT (78498)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

inline long long Norm(long long n)
{
    return (n < 0) ? -n : n;
}

void Sieve()
{
    int curr_pos = 0;
    sieve_visited[0] = sieve_visited[1] = true;
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
}

bool IsPrime(long long n)
{
    if (n < SIEVE_RANGE)
    {
        return !sieve_visited[n];
    }
    for (long long i = 0; i < PRIME_COUNT && (primes[i] * primes[i] <= n); i++)
    {
        if (n == primes[i])
        {
            return true;
        }
        if (n % primes[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

bool IsTopVertexMatched(long long layer)
{
    return IsPrime(6*layer + 1) && IsPrime(12*layer + 5) 
        && IsPrime(6*layer - 1);
}

bool IsEdgeLeftToTopVertexMatched(long long layer)
{
    return (layer > 1) && IsPrime(12*layer - 7) 
        && IsPrime(6*layer + 5) && IsPrime(6*layer - 1);
}

void Solve()
{
    int matched_count = 1; // PD(1) = 3
    for (long long layer = 1; ; layer++)
    {
        if (IsTopVertexMatched(layer))
        {
            matched_count++;
        }
        if (matched_count == 2000)
        {
            std::cout << 2 + 3*layer*(layer-1) << std::endl;
            break;
        }
        if (IsEdgeLeftToTopVertexMatched(layer))
        {
            matched_count++;
        }
        if (matched_count == 2000)
        {
            std::cout << 1 + 3*layer*(layer-1) + 6*layer << std::endl;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
