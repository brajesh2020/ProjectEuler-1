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

long long EulerPhiFunction(long long n)
{
    long long rv = n;
    for (long long i = 0; i < 3432 && (prime[i] * prime[i] <= n); i++)
    {
        if (n % prime[i] == 0) 
        {
            rv /= prime[i];
            rv *= (prime[i] - 1);
        }
        while (n % prime[i] == 0)
        {
            n /= prime[i];
        }
    }
    if (n > 1)
    {
        rv /= n;
        rv *= (n-1);
    }
    return rv;
}

int digit_a[10] = {};
int digit_b[10] = {};
bool HasPermutation(long long a, long long b)
{
    if (a == 0)
    {
        return b == 0;
    }

    for (int i = 0; i < 10; i++)
    {
        digit_a[i] = 0;
        digit_b[i] = 0;
    }
    while (a)
    {
        digit_a[a%10]++;
        a /= 10;
    }
    while (b)
    {
        digit_b[b%10]++;
        b /= 10;
    }

    for (int i = 0; i < 10; i++)
    {
        if (digit_a[i] != digit_b[i])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    long long min_n = 87109;
    long long min_phi = 79180;
    long long phi;
    for (long long n = 2; n <= 10000000; n++)
    {
        phi = EulerPhiFunction(n);
        if (n * min_phi >= min_n * phi)
        {
            continue;
        }
        if (!HasPermutation(n, phi))
        {
            continue;
        }
        min_n = n;
        min_phi = phi;
    }
    printf("%lld/%lld\n", min_n, min_phi);
    return 0;
}