#include <iostream>
#include <stdio.h>

bool visited[10000] = {};
long long S[1230] = {};

inline void InitPrimeCoins() 
{
    S[0] = 0;
    int curr_pos = 1;
    for (long long i = 2; i < 10000; i++) 
    {
        if (!visited[i]) 
        {
            S[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 10000; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

long long coin_change[10000][1230];

int main(int argc, char* argv[])
{
    InitPrimeCoins();

    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < 1230; j++)
        {
            if (i == 0)
            {
                coin_change[i][j] = 1;
            }
            else if (j == 0)
            {
                coin_change[i][j] = 0;
            }
            else if (S[j] > i)
            {
                coin_change[i][j] = coin_change[i][j-1];
            }
            else
            {
                coin_change[i][j] = coin_change[i][j-1] + coin_change[i-S[j]][j];
            }
        }
    }
    for (int i = 2; i < 10000; i++)
    {
        if (coin_change[i][1229] > 5000)
        {
            std::cout << i << " " << coin_change[i][1229] << std::endl;
            break;
        }
    }
    return 0;
}