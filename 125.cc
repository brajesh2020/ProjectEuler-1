#include <iostream>
#include <set>
#include <stdio.h>

int digit[9] = {};
bool IsPalindromicNumber(long long n)
{
    int pos = 0;
    for (long long d = n; d; pos++)
    {
        digit[pos] = d % 10;
        d /= 10;
    }

    for (int i = 0; i < pos/2; i++)
    {
        if (digit[i] != digit[pos-1-i])
        {
            return false;
        }
    }
    return true;
}

long long square_sum[10001] = {};
void InitSquareSumTable()
{
    for (long long i = 1; i <= 10000; i++)
    {
        square_sum[i] = square_sum[i-1] + i*i;
    }
}

std::set<long long> good_numbers;
int main(int argc, char* argv[])
{
    InitSquareSumTable();

    long long n;
    for (long long i = 10000; i >= 0; i--)
    {
        for (long long j = i-2; j >= 0; j--)
        {
            n = square_sum[i] - square_sum[j];
            if (n > 100000000)
            {
                break;
            }
            if (IsPalindromicNumber(n))
            {
                good_numbers.insert(n);
            }
        }
    }

    long long total = 0;
    for (std::set<long long>::iterator it = good_numbers.begin();
        it != good_numbers.end(); it++)
    {
        total += (*it);
    }
    std::cout << total << std::endl;
    return 0;
}