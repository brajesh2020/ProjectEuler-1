#include <iostream>
#include <stdio.h>

long long d;
int digit[10] = {};
int pos;
int curr_sum_digit;
int carry;

bool IsReversibleNumber(long long n)
{
    d = n;
    pos = 0;
    for (; d; pos++)
    {
        digit[pos] = d % 10;
        d /= 10;
    }

    curr_sum_digit = 0;
    carry = 0;
    for (int i = 0; i < pos; i++)
    {
        curr_sum_digit = carry + digit[i] + digit[pos-1-i];
        if (curr_sum_digit % 2 == 0)
        {
            return false;
        }
        carry = curr_sum_digit/10;
    }
    return true;
}

int main(int argc, char* argv[])
{
    long long count = 0;
    for (long long n = 1; n < 1000000000; n++)
    {
        if ((n % 10) && IsReversibleNumber(n))
        {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}