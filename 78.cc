#include <iostream>
#include <stdio.h>

long long coin_change[100001] = {};

int main(int argc, char* argv[])
{
    coin_change[0] = 1;
    for (int i = 0; i < 100001; i++)
    {
        for (int j = i+1; j < 100001; j++)
        {
            coin_change[j] += coin_change[j-i-1];
            coin_change[j] %= 1000000;
        }
        if (coin_change[i] == 0)
        {
            std::cout << i << " => " << coin_change[i] << std::endl;
            break;
        }
    }
    return 0;
}