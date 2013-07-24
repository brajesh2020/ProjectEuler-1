#include <iostream>
#include <stdio.h>

bool A(long long n, long long limit)
{
    long long k = 1;
    long long r = 1;
    while (r)
    {
        r = r * 10 + 1;
        r %= n;
        k++;
        if (k > limit)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    for (long long n = 1000001; ; n += 2)
    {
        if (n%5 && A(n, 1000000))
        {
            std::cout << n << std::endl;
            break;
        }
    }
    return 0;
}
