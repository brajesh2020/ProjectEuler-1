#include <iostream>
#include <stdio.h>

long long T[25] = {};

int main(int argc, const char* argv[])
{
    for (int i = 0; i < 25; i++)
    {
        T[i] = 1;
    }

    for (int i = 1; i <= 20; i++)
    {
        for (int j = 1; j <= 20; j++)
        {
            T[j] += T[j-1];
        }
    }

    std::cout << T[20] << std::endl;
    
	return 0;
}
