#include <iostream>
#include <math.h>
#include <stdio.h>

#define SIEVE_RANGE (64000000)

bool sieve_visited[SIEVE_RANGE] = {};
long long sigma2[SIEVE_RANGE] = {};

bool IsSquare(long long n)
{
    long long x = (long long)sqrt(double(n));
    for (long long i = x - 1; i <= x + 1; i++)
    {
        if (i * i == n)
        {
            return true;
        }
    }
    return false;
}

long long Sigma2(long long prime, long long power)
{
    long long rv = 0;
    long long term = 1;
    for (long long i = 0; i <= power; i++)
    {
        rv += term;
        term = term * prime * prime;
    }
    return rv;
}

void Sieve()
{
    sieve_visited[0] = sieve_visited[1] = true;
    for (long long i = 0; i < SIEVE_RANGE; i++)
    {
        sigma2[i] = 1;
    }

    long long d, power;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            sigma2[i] = Sigma2(i, 1);
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
                d = j;
                power = 0;
                while (d % i == 0)
                {
                    d /= i;
                    power++;
                }
                sigma2[j] *= Sigma2(i, power);

                if (sigma2[j] < 0)
                {
                    std::cout << "!!" << std::endl;
                }
            }
        }
    }
}

void Solve()
{
    long long sum = 0;
    for (long long n = 1; n < SIEVE_RANGE; n++)
    {
        if (IsSquare(sigma2[n]))
        {
            std::cout << n << " => " << sigma2[n] << std::endl;
            sum += n;
        }
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
