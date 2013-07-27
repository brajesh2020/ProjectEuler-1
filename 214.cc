#include <iostream>
#include <stdio.h>

bool visited[40000000] = {};
long long prime[2433654] = {};
long long phi[40000000] = {};

inline void InitPrimeAndPhiTable()
{
    for (long long i = 0; i < 40000000; i++)
    {
        phi[i] = i;
    }

    long long curr_pos = 0;
    for (long long i = 2; i < 40000000; i++)
    {
        if (!visited[i])
        {
            phi[i] = i-1;
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 40000000; j += i)
            {
                phi[j] = phi[j]/i * (i-1);
                visited[j] = true;
            }
        }
    }
}

long long GetChainLength(long long n, long long limit)
{
    long long length = 1;
    long long d = n;
    while (d != 1 && length <= limit)
    {
        d = phi[d];
        length++;
    }
    return (length <= limit) ? length : -1;
}

int main(int argc, char* argv[])
{
    InitPrimeAndPhiTable();
    long long length;
    long long sum = 0;
    for (int i = 0; i < 2433654; i++)
    {
        length = GetChainLength(prime[i], 25);
        if (length == 25) 
        {
            sum += prime[i];
        }
    }
    std::cout << sum << std::endl;
    return 0;
}