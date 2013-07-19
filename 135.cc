#include <iostream>
#include <stdio.h>

int S(int n)
{
    int count = 0;

    int j;
    int d;
    for (int i = 1; i*i <= n; i++)
    {
        if (n % i)
        {
            continue;
        }
        
        j = n/i;
        if ((i+j) % 4)
        {
            continue;
        }

        d = (i+j)/4;
        if (i > d)
        {
            count++;
        }
        if (i != j && j > d)
        {
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    int count = 0;
    for (int n = 1; n < 1000000; n++)
    {
        if (S(n) == 10)
        {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}