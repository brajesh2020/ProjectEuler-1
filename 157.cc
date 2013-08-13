#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

bool visited[50000] = {};
long long prime[5133] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 50000; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 50000; j += i)
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
    for (long long i = 0; i < 5133 && (prime[i] * prime[i] <= d); i++)
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

std::vector<long long> Factorize(long long n)
{
    std::set<long long> divisor_set;
    for (long long i = 1; i*i <= n; i++)
    {
        if (n % i == 0)
        {
            divisor_set.insert(i);
            divisor_set.insert(n/i);
        }
    }
    std::vector<long long> divisors;
    for (std::set<long long>::iterator it = divisor_set.begin();
        it != divisor_set.end(); it++)
    {
        divisors.push_back(*it);
    }
    return divisors;
}

long long GCD(long long a, long long b) 
{
    while (b) 
    {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

long long GetCount(long long n)
{
    long long count = 0;
    std::vector<long long> divisors = Factorize(n);
    long long sigma = divisors.size();
    long long p;
    for (int i = 0; i < sigma; i++)
    {
        for (int j = i; j < sigma; j++)
        {
            if (GCD(divisors[i], divisors[j]) != 1)
            {
                continue;
            }
            p = (divisors[i] + divisors[j]) * n / divisors[i] / divisors[j];
            count += SigmaFunction(p);
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    long long total_count = 0;
    long long base = 10;
    for (long long n = 1; n <= 9; n++)
    {
        total_count += GetCount(base);
        base *= 10;
    }
    std::cout << total_count << std::endl;
    return 0;
}