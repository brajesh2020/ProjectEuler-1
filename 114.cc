#include <iostream>
#include <stdio.h>

long long ways[51] = { 1, 1, 1, 2 };

inline void InitWays()
{
    for (int i = 4; i <= 50; i++)
    {
        ways[i] = 1 + ways[i-1];
        for (int j = 3; j < i; j++)
        {
            ways[i] += ways[i-j-1];
        }
    }
}

int main(int argc, char* argv[])
{
    InitWays();
    std::cout << ways[50] << std::endl;
    return 0;
}