#include <iostream>
#include <map>
#include <stdio.h>

long long type[1000001] = {};

void InitTypeQuery()
{
    long long corners, n;
    for (long long t = 1; t < 500; t++)
    {
        corners = 4*t*t;
        for (long long k = 4; ; k += 4)
        {
            n = k*t + corners;
            if (n > 1000000)
            {
                break;
            }
            type[n]++;
        }
    }
}

std::map<long long, int> counting;

void Sort()
{
    for (long long i = 0; i < 1000001; i++)
    {
        counting[type[i]]++;
    }
}

int main(int argc, char* argv[])
{
    InitTypeQuery();
    Sort();
    long long sum = 0;
    for (long long i = 1; i <= 10; i++)
    {
        sum += counting[i];
    }
    std::cout << sum << std::endl;
    return 0;
}