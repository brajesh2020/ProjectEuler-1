#include <iostream>
#include <set>
#include <stdio.h>

#define SIEVE_RANGE (100)
#define PRIME_COUNT (25)

bool sieve_visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {};

void Sieve()
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
}

long long Count(long long bound)
{
    std::set<long long> numbers;
    numbers.insert(1);
    
    long long next;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        std::cout << prime[i] << " " << numbers.size() << std::endl;
        std::set<long long> temp;
        std::copy(numbers.begin(), numbers.end(), 
            std::inserter(temp, temp.begin()));
        long long power = 1;
        do
        {
            for (std::set<long long>::iterator it = temp.begin();
                it != temp.end(); it++)
            {
                next = (*it) * power;
                if (next > bound)
                {
                    break;
                }
                numbers.insert(next);
            }
            power *= prime[i];
        }
        while (power <= bound);
    }
    return numbers.size();
}

int main(int argc, char* argv[])
{
    Sieve();
    std::cout << Count(1000000000) << std::endl;
    return 0;
}
