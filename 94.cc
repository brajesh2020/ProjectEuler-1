#include <iostream>
#include <stdio.h>

#define PERIMETER_LIMIT (1000000000)

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

long long GetAlmostEquilateralTrianglePerimeter(long long m, long long n)
{
    if (Norm(m*m + n*n - 4*m*n) == 1)
    {
        return 2*(m*m + n*n + 2*m*n);
    }
    if (Norm(-m*m + 3*n*n) == 1)
    {        
        return 4*m*m;
    }
    return 0;
}

int main()
{
    long long total_perimeter = 0;
    long long perimeter;
    for (long long n = 1; 4*n*n < PERIMETER_LIMIT; n++)
    {
        for (long long m = n+1; 3*(m*m+n*n)-1 <= PERIMETER_LIMIT; m += 2)
        {
            if (GCD(m, n) > 1)
            {
                continue;
            }
            perimeter = GetAlmostEquilateralTrianglePerimeter(m, n);
            if (perimeter)
            {
                std::cout << m << " " << n << " => " << perimeter << std::endl;
                if (perimeter <= PERIMETER_LIMIT)
                {
                    total_perimeter += perimeter;
                }
            }
        }
    }
    std::cout << total_perimeter << std::endl;
    return 0;
}