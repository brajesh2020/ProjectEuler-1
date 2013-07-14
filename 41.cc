#include <algorithm>
#include <iostream>
#include <stdio.h>

bool visited[10000] = {};
long long prime[1229] = {};

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

bool IsPrime(long long n) 
{
    for (long long i = 0; i < 1229 && (prime[i] * prime[i] <= n); i++) 
    {
        if (n == prime[i]) 
        {
            return true;
        }
        if (n % prime[i] == 0) 
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

int digit[8] = {};
void PrintPandigitalPrime(int n)
{
    for (int i = 0; i < n; i++)
    {
        digit[i] = i+1;
    }
    do
    {
        long long a = 0;
        for (int i = 0; i < n; i++)
        {
            a *= 10;
            a += digit[i];
        }

        if (IsPrime(a))
        {
            printf("Pandigital prime is %lld\n", a);
        }
    }
    while (std::next_permutation(digit, digit+n));
}

int main(int argc, const char* argv[]) 
{
    InitPrimeTable();

    // n = 9 is impossible.
    // The digit sum = 45 implies any pandigital number is divided by 9.
    for (int n = 1; n <= 8; n++)
    {
        PrintPandigitalPrime(n);
    }
    
    return 0;
}