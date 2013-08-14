#include <iostream>
#include <stdio.h>

int main()
{
    long long T[20] = {};
    T[0] = 3;
    T[1] = 15;
    for (int i = 2; i < 20; i++)
    {
        T[i] = 6 * T[i-1] - T[i-2] - 2;
        if (T[i] > 710000000000)
        {
            std::cout << T[i] << std::endl;
            break;
        }
    }
    return 0;
}