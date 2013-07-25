#include <iostream>
#include <math.h>
#include <stdio.h>

bool IsTerminatingDecimal(long long n)
{
    long long d = n;
    while (d % 2 == 0)
    {
        d /= 2;
    }
    while (d % 5 == 0)
    {
        d /= 5;
    }
    return d == 1;
}

long long GreatestCommonDivisor(long long a, long long b) 
{
    while (b) 
    {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

long long D(long long N)
{
    long long k = (long long)(exp(log(double(N)) - 1.0));
    double r = double(k+1)/double(N) * pow(1.0 + 1.0/double(k), double(k));
    long long k_exact = (r > 1.0) ? k : k+1;
    long long gcd = GreatestCommonDivisor(N, k_exact);
    return IsTerminatingDecimal(k_exact / gcd) ? -N : N;
}

int main(int argc, char* argv[])
{
    long long sum = 0;
    for (long long N = 5; N <= 10000; N++)
    {
        sum += D(N);
    }
    std::cout << sum << std::endl;
    return 0;
}
