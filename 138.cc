#include <iostream>
#include <stdio.h>

int main()
{
    long long m = 4;
    long long n = 1;
    long long sum = 0;
    for (int i = 0; i < 12; i++)
    {
        sum += m*m + n*n;
        long long t = n;
        n = m;
        m = 4*m + t;
    }
    std::cout << sum << std::endl;
    return 0;
}