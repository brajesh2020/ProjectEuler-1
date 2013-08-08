#include <iostream>
#include <stdio.h>

#define N (20)
#define CONSECUTIVE_DIGIT_SUM_LIMIT (9)

long long T[N][10][10] = {};

void InitQueryTable()
{
    for (int j = 1; j < 10; j++)
    {
        T[0][0][j] = 1;
    }
    for (int n = 1; n < N; n++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (i + j + k <= CONSECUTIVE_DIGIT_SUM_LIMIT)
                    {
                        T[n][j][k] += T[n-1][i][j];
                    }
                }
            }
        }
    }
}

long long GetCount()
{
    long long count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            count += T[N-1][i][j];
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    InitQueryTable();
    std::cout << GetCount() << std::endl;
    return 0;
}
