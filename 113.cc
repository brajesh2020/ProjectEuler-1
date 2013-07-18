#include <iostream>
#include <stdio.h>

long long T[100][10] = {};
long long S[100][10] = {};

void InitIncreasingMatrix()
{
    for (int j = 1; j < 10; j++)
    {
        T[0][j] = 1;
    }
    for (int i = 1; i < 100; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            for (int k = 1; k <= j; k++)
            {
                T[i][j] += T[i-1][k];
            }
        }
    }
}

void InitDecreasingMatrix()
{
    for (int j = 1; j < 10; j++)
    {
        S[0][j] = 1;
    }
    for (int i = 1; i < 100; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = j; k < 10; k++)
            {
                S[i][j] += S[i-1][k];
            }
        }
    }
}

long long CountNotBouncyNumber()
{
    long long count = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            count += T[i][j];
            count += S[i][j];
        }
    }
    count -= 9 * 100; // both increasing and decreasing numbers
    return count;
}

int main(int argc, char* argv[])
{
    InitIncreasingMatrix();
    InitDecreasingMatrix();
    std::cout << CountNotBouncyNumber() << std::endl;
    return 0;
}