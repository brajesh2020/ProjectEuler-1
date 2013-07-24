#include <iostream>
#include <stdio.h>

long long ways[51] = {};

inline void InitWays()
{
    ways[1] = 1;
    ways[2] = 2;
    ways[3] = 4;
    ways[4] = 8;
    for (int i = 5; i <= 50; i++)
    {
        ways[i] = ways[i-1] + ways[i-2] + ways[i-3] + ways[i-4];
    }
}

int main(int argc, char* argv[])
{
    InitWays();
    std::cout << ways[50] << std::endl;
    return 0;
}