#include <iostream>
#include <stdio.h>

long long S[100] = {};
long long coin_change[101][100];

int main(int argc, char* argv[])
{
    for (int i = 0; i < 100; i++)
    {
        S[i] = i;
    }

    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 100; j++)
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
    std::cout << coin_change[100][99] << std::endl;
    return 0;
}