#include <iostream>
#include <set>
#include <stdio.h>

int sieve_visited[51] = {};
int prime[15] = {};

inline void InitPrimeTable()
{
    int curr_pos = 0;
    for (int i = 2; i <= 50; i++)
    {
        if (!sieve_visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (int j = i + i; j < 51; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
}

int factorial[51][15] = {};

inline void InitFactorialFactorizations()
{
    for (int i = 2; i <= 50; i++)
    {
        int d = i;
        for (int j = 0; j < 15; j++)
        {
            factorial[i][j] = factorial[i-1][j];
            while (d % prime[j] == 0)
            {
                factorial[i][j]++;
                d /= prime[j];
            }
        }
    }
}

bool IsSquarefreeBinomialNumber(int n, int k)
{
    for (int j = 0; j < 15; j++)
    {
        if (factorial[n][j] - factorial[k][j] - factorial[n-k][j] >= 2)
        {
            return false;
        }
    }
    return true;
}

long long GetBinomialNumber(int n, int k)
{
    if (n - k < k)
    {
        k = n - k;
    }
    long long num = 1;
    for (int i = n; i > n-k; i--) 
    {
        num = num * i / (n+1-i);
    }
    return num;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitFactorialFactorizations();

    std::set<long long> results;
    for (int n = 0; n <= 50; n++)
    {
        for (int k = 0; k <= n/2; k++)
        {
            if (IsSquarefreeBinomialNumber(n, k))
            {
                results.insert(GetBinomialNumber(n, k));
            }
        }
    }

    long long sum = 0;
    for (std::set<long long>::iterator it = results.begin();
        it != results.end(); it++)
    {
        sum += (*it);
    }
    std::cout << sum << std::endl;
    return 0;
}