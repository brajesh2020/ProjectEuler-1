#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[])
{
    long long count = 0;
    for (long long t = 1; t < 500; t++)
    {
        count += (250000 - t*t)/t;
    }
    std::cout << count << std::endl;

    return 0;
}