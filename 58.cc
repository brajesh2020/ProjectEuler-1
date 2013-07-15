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

int main(int argc, const char* argv[])
{
    InitPrimeTable();

    long long total_count = 1;
    long long prime_count = 0;

    // 3 = 1^2 + 2, 13 = 3^2 + 4, 31 = 5^2 + 6
    for (int i = 1; ; i += 2)
    {
        total_count += 4;
        long long first = i*i + i + 1;
        for (int j = 0; j < 4; j++)
        {
            if (IsPrime(first + j * (i + 1)))
            {
                prime_count++;
            }
        }

        if (prime_count * 10 < total_count)
        {
            std::cout << i+2 << std::endl;
            break;
        }
    }
	return 0;
}
