#include <iostream>
#include <stdio.h>

long long query[40][10][10][10] = {};

inline void InitQueryTable()
{
    int next_r, next_s;
    for (int j = 1; j <= 9; j++)
    {
        query[0][j][j][j] = 1;
    }

    for (int i = 1; i < 40; i++)
    {
        for (int j = 0; j <= 8; j++)
        {
            for (int r = 0; r < 10; r++)
            {
                for (int s = 0; s < 10; s++)
                {
                    if (j < r)
                    {
                        query[i][j][r-1][s] += query[i-1][j+1][r][s];
                    }
                    else
                    {
                        query[i][j][r][s] += query[i-1][j+1][r][s];
                    }
                }
            }
        }

        for (int j = 1; j <= 9; j++)
        {
            for (int r = 0; r < 10; r++)
            {
                for (int s = 0; s < 10; s++)
                {
                    if (j > s)
                    {
                        query[i][j][r][s+1] += query[i-1][j-1][r][s];
                    }
                    else
                    {
                        query[i][j][r][s] += query[i-1][j-1][r][s];
                    }
                }
            }
        }       
    }
}

int main(int argc, char* argv[])
{
    InitQueryTable();

    long long count = 0;
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            count += query[i][j][0][9];
        }
    }
    std::cout << "Count: " << count << std::endl;
    return 0;
}