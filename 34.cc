#include <iostream>
#include <stdio.h>
#include <string.h>

long long factorials[10] = {};

void InitFactorials()
{
    factorials[0] = 1;
    for (int i = 1; i <= 9; i++)
    {
        factorials[i] = factorials[i-1] * i;
    }
}

long long DigitFactorialSum(long long n)
{
    long long sum = 0;
    while (n)
    {
        sum += factorials[n % 10];
        n /= 10;
    }
    return sum;
}

int main(int argc, char* argv[])
{
    InitFactorials();
    for (long long i = 10; i < 10000000; i++)
    {
        if (DigitFactorialSum(i) == i)
        {
            std::cout << i << std::endl;
        }
    }
    return 0;
}