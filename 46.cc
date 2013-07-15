#include <iostream>
#include <stdio.h>

bool visited[47000] = {};
long long prime[4851] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 47000; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 47000; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

bool IsPrime(long long n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long i = 0; i < 4851 && (prime[i] * prime[i] <= n); i++)
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

bool HasPassGoldbachConjecture(long long n)
{
    if (IsPrime(n))
    {
        return true;
    }

    long long p;
    bool found = false;
    for (long long i = 1; 2 * i * i < n; i++)
    {
        if (IsPrime(n - 2 * i * i))
        {
            found = true;
            break;
        }
    }
    return found;
}

int main(int argc, const char* argv[])
{
    InitPrimeTable();

    for (long long n = 9; ; n += 2)
    {
        if (!HasPassGoldbachConjecture(n))
        {
            std::cout << n << std::endl;
            break;
        }
    }
    return 0;
}
