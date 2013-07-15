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

long long abundant[7179] = {};

void InitAbundantNumberTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 29000; i++)
    {
        if (ProperSigmaFunction(i) > i)
        {
            abundant[curr_pos] = i;
            curr_pos++;
        }
    }
}

bool visited_sum[29000] = {};

void VisitSumOfTwoAbundantNumbers()
{
    long long sum;
    for (long long i = 0; i < 7179; i++)
    {
        for (long long j = 0; j < 7179; j++)
        {
            sum = abundant[i] + abundant[j];
            if (sum < 29000)
            {
                visited_sum[sum] = true;
            }
            else
            {
                break;
            }
        }
    }
}

void PrintSolution()
{
    long long sum = 0;
    for (long long i = 1; i <= 28123; i++)
    {
        if (!visited_sum[i])
        {
            sum += i;
        }
    }

    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitAbundantNumberTable();
    VisitSumOfTwoAbundantNumbers();
    PrintSolution();
    return 0;
}