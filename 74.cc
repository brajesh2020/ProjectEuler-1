#include <iostream>
#include <set>
#include <stdio.h>

long long factorial[10] = {};

inline void InitFactorial()
{
    factorial[0] = 1;
    for (int i = 1; i < 10; i++)
    {
        factorial[i] = factorial[i-1] * i;
    }
}

long long DigitFactorialSum(long long n)
{
    if (n == 0)
    {
        return 1;
    }
    long long sum = 0;
    while (n)
    {
        sum += factorial[n % 10];
        n /= 10;
    }
    return sum;
}

std::set<long long> chains;
int GetDigitFactorialCycle(long long n)
{
    chains.clear();
    long long cycle = 1;
    long long next = n;
    do 
    {
        chains.insert(next);
        next = DigitFactorialSum(next);
    }
    while (chains.find(next) == chains.end());
    return chains.size();
}

int main(int argc, char* argv[])
{
    InitFactorial();
    int count = 0;
    for (long long i = 1; i < 1000000; i++)
    {
        if (GetDigitFactorialCycle(i) == 60)
        {
            count++;
            std::cout << i << std::endl;
        }
    }
    std::cout << count << std::endl;
    return 0;
}