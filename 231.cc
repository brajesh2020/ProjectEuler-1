#include <iostream>
#include <stdio.h>
#define MAX (20000001)

bool visited[MAX] = {};
long long query[MAX] = {};
long long d[MAX] = {};

inline void InitQueryTable()
{
    for (long long i = 0; i < MAX; i++)
    {
        d[i] = i;
    }

    long long prime_power;
    for (long long i = 2; i < MAX; i++)
    {
        if (!visited[i])
        {
            query[i] = i;
            for (long long j = i + i; j < MAX; j += i)
            {
                prime_power = 0;
                while (d[j] % i == 0)
                {
                    d[j] /= i;
                    prime_power++;
                }
                query[j] = query[j] + i * prime_power;
                visited[j] = true;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitQueryTable();

    long long rv = 0;
    for (long long i = 20000000 - 5000000 + 1; i <= 20000000; i++)
    {
        rv += query[i];
    }
    for (long long i = 1; i <= 5000000; i++)
    {
        rv -= query[i];
    }
    std::cout << rv << std::endl;

    return 0;
}