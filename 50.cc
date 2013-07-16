#include <iostream>
#include <stdio.h>

bool visited[1000000] = {};
long long prime[78498] = {};
long long prime_sum[78499] = {};

inline void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < 1000000; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            prime_sum[curr_pos + 1] += prime_sum[curr_pos] + i;
            curr_pos++;
            for (long long j = i + i; j < 1000000; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

int main(int argc, const char* argv[]) 
{
    InitPrimeTable();

    long long max_len = 21;
    long long that_prime = 953;
    for (long long i = 0; i <= 78498; i++)
    {
        for (long long j = i + 1; j <= 78498; j++)
        {
            long long diff = prime_sum[j] - prime_sum[i];
            if (diff >= 1000000)
            {
                break;
            }
            if ((j - i > max_len) && (!visited[diff]))
            {
                max_len = j - i;
                that_prime = diff;
            }
        }
    }
    std::cout << that_prime << std::endl;
    
    return 0;
}