#include <iostream>
#include <stdio.h>

bool visited[10000002] = {};
long long prime[664579] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 10000002; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 10000002; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

long long ModPow(long long a, long long n, long long mod)
{
    long long rv = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1)
        {
            rv *= a;
            rv %= mod;
        }
        a *= a;
        a %= mod;
    }
    return rv % mod;
}

bool IsRepunitDividedBy(long long divisor, long long power)
{
    return ModPow(10, power, divisor * 9) == 1;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();

    long long prime_count = 0;
    long long prime_sum = 0;
    for (int i = 0; i < 664579; i++)
    {
        if (IsRepunitDividedBy(prime[i], 1000000000))
        {
            prime_count++;
            prime_sum += prime[i];
            std::cout << prime_count << " => " << prime[i] << std::endl;
            if (prime_count == 40)
            {
                std::cout << prime_sum << std::endl;
                break;
            }
        }
    }
    return 0;
}
