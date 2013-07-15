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

long long ProperSigmaFunction(long long n)
{
    long long d = n;
    long long sigma = 1;
    long long prime_sum, prime_power;
    for (long long i = 0; i < 3432 && (prime[i] * prime[i] <= d); i++)
    {
        prime_sum = 1;
        prime_power = prime[i];
        while (d % prime[i] == 0)
        {
            d /= prime[i];
            prime_sum += prime_power;
            prime_power *= prime[i];
        }
        sigma *= prime_sum;
    }

    if (d > 1) 
    {
        sigma *= (1 + d);
    }
    return sigma - n;
}

long long proper_sigma[10001] = {};

void InitProperSigmaTable()
{
    for (int i = 2; i < 10001; i++)
    {
        proper_sigma[i] = ProperSigmaFunction(i);
    }
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitProperSigmaTable();

    long long sum = 0;
    for (long long i = 2; i < 10001; i++)
    {
        if (proper_sigma[i] > i && proper_sigma[i] < 10001 && 
            proper_sigma[proper_sigma[i]] == i)
        {
            sum = sum + i + proper_sigma[i];
        }
    }
    
    std::cout << sum << std::endl;
    return 0;
}