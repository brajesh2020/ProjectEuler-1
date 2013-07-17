#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

bool visited[1000001] = {};
long long sigma[1000001] = {};

inline void InitSigmaTable()
{
    for (long long i = 1; i < 1000001; i++)
    {
        sigma[i] = 1;
    }

    long long d;
    long long prime_sum, prime_power;
    for (long long i = 2; i < 1000001; i++)
    {
        if (!visited[i])
        {
            sigma[i] += i;
            for (long long j = i + i; j < 1000001; j += i)
            {
                visited[j] = true;
                d = j;
                prime_sum = 1;
                prime_power = i;
                while (d % i == 0)
                {
                    d /= i;
                    prime_sum += prime_power;
                    prime_power *= i;
                }
                sigma[j] *= prime_sum;
            }
        }
    }

    for (long long i = 1; i < 1000001; i++)
    {
        sigma[i] -= i;
    }
}

int main(int argc, char* argv[])
{
    InitSigmaTable();

    // DFS
    bool chain_visited[1000001] = {};
    std::vector<long long> chains;
    long long curr;

    for (long long i = 6; i <= 1000000; i++)
    {
        chains.clear();
        curr = i;

        while (curr <= 1000000 && !chain_visited[curr])
        {
            chain_visited[curr] = true;
            chains.push_back(curr);
            curr = sigma[curr];
        }

        // Dead chain
        if (curr > 1000000)
        {
            continue;
        }

        // Try to find chain cycle
        int chain_len = chains.size();
        int pos = 0;
        for (; (pos < chain_len) && (chains[pos] != curr); pos++);
        if (pos == chain_len)
        {
            continue;
        }

        // Print all possible chains.
        for (int j = pos; j < chain_len; j++)
        {
            std::cout << chains[j];
            if (j == chain_len - 1)
            {
                std::cout << std::endl;
            }
            else
            {
                std::cout << " => ";
            }
        }
    }
    
    return 0;
}