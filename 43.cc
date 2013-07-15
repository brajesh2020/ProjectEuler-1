#include <algorithm>
#include <iostream>
#include <stdio.h>

int digit[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int divisor[7] = { 2, 3, 5, 7, 11, 13, 17 };
int sum[11] = {};

inline bool IsDivided(int pos, int d)
{
    return (digit[pos]*100 + digit[pos+1]*10 + digit[pos+2]) % d == 0;
}

inline bool IsMatched()
{
    for (int i = 0; i < 7; i++)
    {
        if (!IsDivided(i+1, divisor[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    do 
    {
        if (IsMatched())
        {
            for (int i = 0; i < 10; i++)
            {
                sum[i+1] += digit[i];
            }
        }
    } 
    while (std::next_permutation(digit, digit+10));       

    for (int i = 10; i > 0; i--)
    {
        if (sum[i] > 10)
        {
            sum[i-1] += sum[i]/10;
            sum[i] %= 10;
        }
    }

    for (int i = 0; i < 11; i++)
    {
        printf("%d", sum[i]);
    }
    putchar('\n');
 
    return 0;
}