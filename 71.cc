#include <iostream>
#include <stdio.h>
#include <string.h>

// Euclidean Algorithm
long long GetGCD(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

int main(int argc, char* argv[])
{
    long long nearest_n = 1;
    long long nearest_d = 8;
    long long n;
    for (long long d = 3; d <= 1000000; d++)
    {
        n = (3*d-1)/7;
        while (GetGCD(n, d) != 1)
        {
            n--;
        }
        if (nearest_n * d < n * nearest_d)
        {
            nearest_n = n;
            nearest_d = d;
        }
    }
    printf("%lld/%lld\n", nearest_n, nearest_d);
    
    return 0;
}