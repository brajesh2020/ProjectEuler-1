#include <iostream>
#include <set>
#include <stdio.h>

bool visited[10000002] = {};
long long prime[664579] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 10000002; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 10000002; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

std::set<long long> r_set;
bool IsRepunitDividedBy(long long divisor, long long k)
{
    r_set.clear();
    long long r = 0;
    long long m = 10000000000 % divisor;
    long long u = 1111111111 % divisor;
    for (int i = 0; i < k; i++)
    {
        r = (m*r + u) % divisor;
        
        if (r_set.find(r) != r_set.end())
        {
            return false;
        }
        r_set.insert(r);

        if (r == 0)
        {
            return k % (i+1) == 0;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();

    long long prime_count = 0;
    long long prime_sum = 0;
    for (int i = 0; i < 664579; i++)
    {
        if (IsRepunitDividedBy(prime[i], 100000000))
        {
            prime_count++;
            prime_sum += prime[i];
            std::cout << prime_count << " => " << prime[i] << std::endl;
            if (prime_count == 40)
            {
                std::cout << prime_sum << std::endl;
                break;
            }
        }
    }
    return 0;
}
