#include <iostream>
#include <stdio.h>

long long GetFirstNumberOf(long long len)
{
    long long rv = 1;
    for (int i = 1; i < len; i++)
    {
        rv *= 10;
    }
    return rv;
}

long long GetDigit(long long n)
{
    long long len = 1, count = 9, curr_pos = 1;
    for (; curr_pos + count * len <= n; 
        curr_pos += count * len, len += 1, count *= 10);

    long long diff = n - curr_pos;
    long long which_num = diff / len + GetFirstNumberOf(len);
    long long which_digit_pos = len - diff % len - 1;
    long long d = which_num;
    for (int i = 0; i < which_digit_pos; i++)
    {
        d /= 10;
    }
    return d % 10;
}

// -----------------------------------------------------------------------------

int main(int argc, const char* argv[]) 
{
    long long product = 1;
    long long n = 1;
    for (int i = 0; i < 7; i++)
    {
        product *= GetDigit(n);
        n *= 10;
    }
    std::cout << product << std::endl;
    
    return 0;
}