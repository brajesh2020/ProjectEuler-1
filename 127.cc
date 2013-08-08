#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (120000)

bool sieve_visited[SIEVE_RANGE] = {};
long long rad[SIEVE_RANGE] = {};

void Sieve()
{
    sieve_visited[0] = sieve_visited[1] = true;
    for (long long i = 0; i < SIEVE_RANGE; i++)
    {
        rad[i] = 1;
    }
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            rad[i] *= i;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
                rad[j] *= i;
            }
        }
    }
}

inline long long CoprimeRadical(long long a, long long b, long long c)
{
    return rad[a] * rad[b] * rad[c];
}

bool IsCoprime(long long a, long long b)
{
    while (b) 
    {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a == 1;
}

void Solve()
{
    long long sum = 0;
    long long b;
    for (long long c = 3; c < 120000; c++)
    {
        if (2 * rad[c] >= c)
        {
            continue;
        }
        for (long long a = 1; a + a < c; a++)
        {
            b = c - a;
            if ((CoprimeRadical(a, b, c) < c) && IsCoprime(rad[a], rad[b]))
            {
                sum += c;
                std::cout << a << " " << b << " " << c << std::endl;
            }
        }
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
