#include <iostream>
#include <stdio.h>

bool visited[10000002] = {};
long long prime[664580] = {};

int main(int argc, const char* argv[])
{
    long long n = 1;
    for (long long i = 2; i < 10000002; i++)
    {
        if (!visited[i])
        {
            prime[n] = i;
            if ((n % 2) && prime[n]*n > 5000000000)
            {
                std::cout << prime[n]*n*2 << std::endl;
                std::cout << n << std::endl;
                break;
            }
            n++;

            for (long long j = i + i; j < 10000002; j += i)
            {
                visited[j] = true;
            }
        }
    }
    return 0;
}