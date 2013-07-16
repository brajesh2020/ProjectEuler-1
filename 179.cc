#include <iostream>
#include <stdio.h>
#include <string.h>

bool visited[32000] = {};
long long prime[3432] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 32000; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 32000; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

long long SigmaFunction(long long n)
{
    long long d = n;
    long long sigma = 1;
    for (long long i = 0; i < 3432 && (prime[i] * prime[i] <= d); i++)
    {
        long long prime_power = 0;
        while (d % prime[i] == 0)
        {
            d /= prime[i];
            prime_power++;
        }
        sigma *= (prime_power + 1);
    }

    if (d > 1) 
    {
        sigma *= 2;
    }
    return sigma;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();

    long long count = 0;
    long long prev_sigma = 2;
    long long curr_sigma;
    for (long long n = 3; n <= 10000000; n++)
    {
        curr_sigma = SigmaFunction(n);
        if (curr_sigma == prev_sigma)
        {
            count++;
        }
        prev_sigma = curr_sigma;
    }
    std::cout << "Count: " << count << std::endl;
    return 0;
}