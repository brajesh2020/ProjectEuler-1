#include <algorithm>
#include <iostream>
#include <set>
#include <stdio.h>

int digit[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

long long BuildNumber(long long start_pos, long long end_pos)
{
    long long num = 0;
    for (long long i = start_pos; i < end_pos; i++)
    {
        num *= 10;
        num += digit[i];
    }
    return num;
}

std::set<long long> pandigital_products;

void GeneratePandigitalProduct()
{
    long long a, b, c;
    for (long long i = 1; i < 8; i++)
    {
        for (long long j = i+1; j < 8; j++)
        {
            long long a = BuildNumber(0, i);
            long long b = BuildNumber(i, j);
            long long c = BuildNumber(j, 9);
            if (a * b == c)
            {
                pandigital_products.insert(c);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    do 
    {
        GeneratePandigitalProduct();
    } 
    while (std::next_permutation(digit, digit+9));       

    long long sum = 0;
    for (std::set<long long>::iterator it = pandigital_products.begin();
        it != pandigital_products.end(); it++)
    {
        sum += (*it);
    }
    std::cout << sum << std::endl;

    return 0;
}