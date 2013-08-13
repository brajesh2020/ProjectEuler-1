#include <iostream>
#include <stdio.h>

#define PERIMETER_LIMIT (100000000)

inline long long Norm(long long a)
{
    return (a < 0) ? -a : a;
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

long long GetCount(long long m, long long n)
{
    long long diff = Norm(m*m - n*n - 2*m*n);
    long long c = m*m + n*n;
    if (c % diff == 0)
    {
        std::cout << m*m + n*n << " " << 2*m*n << " " << m*m - n*n << std::endl;
        return PERIMETER_LIMIT / (2*m*(m+n));
    }
    else 
    {
        return 0;
    }
}

int main()
{
    long long total_count = 0;
    for (long long n = 1; 4*n*n < PERIMETER_LIMIT; n++)
    {
        for (long long m = n+1; 2*m*(m+n) <= PERIMETER_LIMIT; m += 2)
        {
            if (GCD(m, n) > 1)
            {
                continue;
            }
            total_count += GetCount(m, n);
        }
    }
    std::cout << total_count << std::endl;
    return 0;
}