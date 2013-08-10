#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (100000)
#define PRIME_COUNT (9592)

bool sieve_visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {};

void Sieve()
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
}

long long A(long long n)
{
    long long k = 1;
    long long r = 1;
    while (r)
    {
        r = r * 10 + 1;
        r %= n;
        k++;
    }
    return k;
}

void Solve()
{
    long long sum = 0;
    long long a;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        if (prime[i] == 2 || prime[i] == 5)
        {
            sum += prime[i];
            continue;
        }
        a = A(prime[i]);
        while (a % 2 == 0)
        {
            a /= 2;
        }
        while (a % 5 == 0)
        {
            a /= 5;
        }
        if (a > 1)
        {
            sum += prime[i];
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
