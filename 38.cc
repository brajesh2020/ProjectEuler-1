#include <algorithm>
#include <iostream>
#include <stdio.h>

int digit[9] = { 9, 1, 8, 2, 7, 3, 6, 4, 5 };

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

long long GetDigitCount(long long n)
{
    long long count = 1;
    long long power = 10;
    while (1)
    {
        if (n < power)
        {
            return count;
        }
        count++;
        power *= 10;
    }
    return -1;
}

void GeneratePandigitalMultiple()
{
    long long g;
    for (long long i = 1; i < 9; i++)
    {
        g = BuildNumber(0, i);

        bool possible = true;
        long long curr_pos = i, digit_count;
        for (long long n = 2; curr_pos < 9; n++)
        {
            digit_count = GetDigitCount(g*n);
            if ((curr_pos + digit_count > 9) || 
                (g*n != BuildNumber(curr_pos, curr_pos + digit_count)))
            {
                possible = false;
                break;
            }            
            curr_pos += digit_count;
        } 
        if (possible)
        {
            std::cout << BuildNumber(0, 9) << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    do 
    {
        GeneratePandigitalMultiple();
    } 
    while (std::next_permutation(digit, digit+9));       

    return 0;
}