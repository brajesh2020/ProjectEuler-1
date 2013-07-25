#include <iostream>
#include <stdio.h>
#define m (50)
#define n (200)

long long ways[n+1] = {};

int main(int argc, char* argv[])
{
    for (int i = 0; i < m; i++)
    {
        ways[i] = 1;
    }
    ways[m] = 2;

    for (int i = m+1; i <= n; i++)
    {
        ways[i] = 1 + ways[i-1];
        for (int j = m; j < i; j++)
        {
            ways[i] += ways[i-j-1];
        }
        if (ways[i] > 1000000)
        {
            std::cout << i << std::endl;
            break;
        }
    }
    return 0;
}