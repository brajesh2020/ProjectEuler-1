#include <iostream>
#include <set>
#include <stdio.h>

#define UPPER_BOUND (50000000)

bool visited[10000] = {};
long long prime[1229] = {};
long long power[1229][3] = {};

inline void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < 10000; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 10000; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

inline void InitPrimePowerTable()
{
    for (long long i = 0; prime[i] < 85; i++)
    {
        power[i][0] = prime[i] * prime[i] * prime[i] * prime[i];
    }
    for (long long i = 0; prime[i] < 369; i++)
    {
        power[i][1] = prime[i] * prime[i] * prime[i];
    }
    for (long long i = 0; prime[i] < 7072; i++)
    {
        power[i][2] = prime[i] * prime[i];
    }
}

std::set<long long> triples;

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitPrimePowerTable();

    long long partial_sum, sum;
    for (long long i = 0; prime[i] < 85; i++)
    {
        for (long long j = 0; prime[j] < 369; j++)
        {
            partial_sum = power[i][0] + power[j][1];
            if (partial_sum > UPPER_BOUND)
            {
                break;
            }
            for (long long k = 0; prime[k] < 7072; k++)
            {
                sum = partial_sum + power[k][2];
                if (sum > UPPER_BOUND)
                {
                    break;
                }
                triples.insert(sum);
            }
        }
    }

    std::cout << triples.size() << std::endl;
    return 0;
}