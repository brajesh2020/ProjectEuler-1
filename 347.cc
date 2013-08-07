#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (10000000)
#define PRIME_COUNT (664579)

bool visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {}; 

void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

long long Pow(long long a, long long n)
{
    long long rv = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1)
        {
            rv *= a;
        }
        a *= a;
    }
    return rv;
}

long long M(long long p, long long q, long long N)
{
    long long max_so_far = 0;
    long long p_pow;
    long long q_pow;
    long long curr;
    for (int i = 1; ; i++)
    {
        p_pow = Pow(p, i);
        if (p_pow > N)
        {
            break;
        }
        for (int j = 1; ; j++)
        {
            q_pow = Pow(q, j);
            curr = p_pow * q_pow;
            if (curr > N)
            {
                break;
            }
            if (curr > max_so_far)
            {
                max_so_far = curr;
            }
        }
    }
    return max_so_far;
}

long long S(long long N)
{
    long long sum = 0;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        if (prime[i] * prime[i] > N)
        {
            break;
        }
        for (int j = i+1; j < PRIME_COUNT; j++)
        {
            if (prime[i] * prime[j] > N)
            {
                break;
            }
            sum += M(prime[i], prime[j], N);
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    std::cout << S(10000000) << std::endl;
    return 0;
}