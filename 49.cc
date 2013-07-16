#include <iostream>
#include <stdio.h>

bool visited[10000] = {};

inline void InitPrimeTable() 
{
    for (long long i = 2; i < 10000; i++) 
    {
        if (!visited[i]) 
        {
            for (long long j = i + i; j < 10000; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

bool ArePermutations(int a, int b, int c)
{
    int digit[3][10] = {};
    while (a)
    {
        digit[0][a % 10]++;
        a /= 10;
    }
    while (b)
    {
        digit[1][b % 10]++;
        b /= 10;
    }
    while (c)
    {
        digit[2][c % 10]++;
        c /= 10;
    }
    for (int i = 0; i < 10; i++)
    {
        if (digit[0][i] != digit[1][i] || digit[1][i] != digit[2][i])
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

int main(int argc, const char* argv[]) 
{
    InitPrimeTable();

    for (int i = 1000; i < 10000; i++)
    {
        if (visited[i])
        {
            continue;
        }
        for (int d = 1; i+2*d < 10000; d++)
        {
            if (!visited[i+d] && !visited[i+2*d] && 
                ArePermutations(i, i+d, i+2*d))
            {
                printf("%d%d%d\n", i, i+d, i+2*d);
            }
        }
    }
    
    return 0;
}