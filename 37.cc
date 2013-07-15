#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>

bool visited[47000] = {};
long long prime[4851] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 47000; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 47000; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

bool IsPrime(long long n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long i = 0; i < 4851 && (prime[i] * prime[i] <= n); i++)
    {
        if (n == prime[i])
        {
            return true;
        }
        if (n % prime[i] == 0)
        {
            return false;
        }
    }
    return true;
}

std::vector<long long> truncatable_primes;

void TryToInsertTruncatablePrime(long long n)
{
    if (n < 10)
    {
        return;
    }
    
    bool possible = true;
    long long power = 10;
    while (power < n)
    {
        if (!IsPrime(n % power))
        {
            possible = false;
            break;
        }
        power *= 10;
    }

    if (possible)
    {
        truncatable_primes.push_back(n);
    }
}

void VisitTruncatablePrimes()
{
    std::queue<long long> prime_queue;
    prime_queue.push(2);
    prime_queue.push(3);
    prime_queue.push(5);
    prime_queue.push(7);

    while (!prime_queue.empty())
    {
        long long top = prime_queue.front();
        TryToInsertTruncatablePrime(top);
        prime_queue.pop();

        long long next = top * 10;
        for (int i = 1; i <= 9; i += 2)
        {
            if (IsPrime(next + i))
            {
                prime_queue.push(next + i);
            }
        }
    }
}

void PrintSolution()
{
    long long sum = 0;
    for (std::vector<long long>::iterator it = truncatable_primes.begin();
        it != truncatable_primes.end(); it++)
    {
        sum += (*it);
        std::cout << "Truncatable Prime: " << (*it) << std::endl;
    }
    std::cout << "Sum: " << sum << std::endl;
}

int main(int argc, const char* argv[])
{
    InitPrimeTable();
    VisitTruncatablePrimes();
    PrintSolution();
	return 0;
}
