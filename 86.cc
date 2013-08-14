#include <iostream>
#include <stdio.h>

inline long long maximum(long long a, long long b)
{
    return (a > b) ? a : b;
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

long long GetCount(long long m, long long n, long long side_limit)
{
    long long count = 0;

    long long primitive_a = m*m - n*n;
    long long primitive_b = 2*m*n;
    long long a, b;

    if (primitive_b <= 2 * primitive_a)
    {
        for (long long t = 1; t * primitive_a <= side_limit; t++)
        {
            a = t * primitive_a;
            b = t * primitive_b;
            count += (b/2 - maximum(1, b-a) + 1);
        }
    }
    if (primitive_a <= 2 * primitive_b)
    {
        for (long long t = 1; t * primitive_b <= side_limit; t++)
        {
            a = t * primitive_a;
            b = t * primitive_b;
            count += (a/2 - maximum(1, a-b) + 1);
        }
    }
    return count;
}

long long Solve(long long side_limit)
{
    long long total_count = 0;
    for (long long n = 1; 2*n*n <= side_limit; n++)
    {
        for (long long m = n+1; 
            m*m-n*n <= side_limit || 2*m*n <= side_limit; m += 2)
        {
            if (GCD(m, n) > 1)
            {
                continue;
            }
            total_count += GetCount(m, n, side_limit);
        }
    }
    return total_count;
}

int main()
{
    for (long long m = 100; ; m++)
    {
        if (Solve(m) > 1000000)
        {
            printf("The number of solutions is %lld when M=%lld\n", Solve(m-1), m-1);
            printf("The number of solutions is %lld when M=%lld\n", Solve(m), m);
            break;
        }
    }
    return 0;
}