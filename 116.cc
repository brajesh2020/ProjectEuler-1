#include <iostream>
#include <stdio.h>

long long red_ways[51] = {};
long long green_ways[51] = {};
long long blue_ways[51] = {};

inline void InitRedWays()
{
    red_ways[2] = 1;
    for (int i = 3; i <= 50; i++)
    {
        red_ways[i] = red_ways[i-1] + red_ways[i-2] + 1;
    }
}

inline void InitGreenWays()
{
    green_ways[3] = 1;
    for (int i = 4; i <= 50; i++)
    {
        green_ways[i] = green_ways[i-1] + green_ways[i-3] + 1;
    }
}

inline void InitBlueWays()
{
    blue_ways[4] = 1;
    for (int i = 5; i <= 50; i++)
    {
        blue_ways[i] = blue_ways[i-1] + blue_ways[i-4] + 1;
    }
}

int main(int argc, char* argv[])
{
    InitRedWays();
    InitGreenWays();
    InitBlueWays();
    std::cout << red_ways[50] + green_ways[50] + blue_ways[50] << std::endl;
    return 0;
}