#include <iostream>
#include <stdio.h>

bool is_ascending;
bool is_descending;
int prev_digit;
int r;
long long d;
long long rearranged;

bool IsBouncyNumber(long long n)
{
    is_ascending = false;
    is_descending = false;
    prev_digit = -1;
    d = n;
    while (d)
    {
        r = d % 10;
        if (prev_digit >= 0)
        {
            if (r > prev_digit)
            {
                is_ascending = true;
            }
            else if (r < prev_digit)
            {
                is_descending = true;
            }
        }
        prev_digit = r;
        d /= 10;
    }
    return is_ascending && is_descending;
}

int main(int argc, const char* argv[])
{
    long long n;
    long long bouncy_count = 0;
    for (n = 1; ; n++)
    {
        if (IsBouncyNumber(n))
        {
            bouncy_count++;
            if (bouncy_count * 10 == n * 9)
            {
                std::cout << "Found 90%: " << bouncy_count << "/" << n << std::endl;
            }
            if (bouncy_count * 100 == n * 99)
            {
                std::cout << "Found 99%: " << bouncy_count << "/" << n << std::endl;
                break;
            }
        }
    }
    return 0;
}
