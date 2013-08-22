#include <iostream>
#include <stdio.h>

#define UPPER_BOUND (1000000)

long long mdrs[UPPER_BOUND] = {};

inline long long maximum(long long a, long long b)
{
    return (a > b) ? a : b;
}

long long GetDigitalRoot(long long n)
{
    long long sum = 0;
    while (n)
    {
        sum += (n % 10);
        n /= 10;
    }
    if (sum >= 10)
    {
        sum = GetDigitalRoot(sum);
    }
    return sum;
}

void InitMaximumDigitalRootSum()
{
    for (long long i = 2; i < UPPER_BOUND; i++)
    {
        mdrs[i] = GetDigitalRoot(i);
        for (long long d = 2; d*d <= i; d++)
        {
            if (i % d == 0)
            {
                mdrs[i] = maximum(mdrs[i], mdrs[d] + mdrs[i/d]);
            }
        }
    }
}

long long GetSum()
{
    long long sum = 0;
    for (long long i = 2; i < UPPER_BOUND; i++)
    {
        sum += mdrs[i];
    }
    return sum;
}

int main()
{
    InitMaximumDigitalRootSum();
    std::cout << GetSum() << std::endl;
    return 0;
}
