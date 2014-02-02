#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (100000000)

bool visited[SIEVE_RANGE + 1] = {};
long long phi[SIEVE_RANGE + 1] = {};

inline void InitPhiTable()
{
    for (long long i = 0; i <= SIEVE_RANGE; i++)
    {
        phi[i] = i;
    }

    long long prime_count = 0;
    for (long long i = 2; i <= SIEVE_RANGE; i++)
    {
        if (!visited[i])
        {
            phi[i] = i-1;
            prime_count++;
            for (long long j = i + i; j <= SIEVE_RANGE; j += i)
            {
                phi[j] = phi[j]/i * (i-1);
                visited[j] = true;
            }
        }
    }

    std::cout << "Prime count: " << prime_count << std::endl;
}

long long H(long long n)
{
    long long rv = n * (n+1) / 2;
    for (long long i = 0; i <= n; i++)
    {
        rv -= phi[i];
    }
    return 6 * rv;
}

int main(int argc, char* argv[])
{
    InitPhiTable();
    std::cout << H(5) << std::endl;
    std::cout << H(10) << std::endl;
    std::cout << H(1000) << std::endl;
    std::cout << H(100000000) << std::endl;
    return 0;
}