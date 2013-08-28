#include <iostream>
#include <math.h>
#include <stdio.h>

#define PROBLEM_RANGE (20000000)
#define OFFSET_COUNT (100)
#define SIEVE_RANGE (45000)
#define PRIME_COUNT (4675)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

void Sieve()
{
    sieve_visited[0] = sieve_visited[1] = true;
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            primes[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
    std::cout << "Sieve completed!" << std::endl;
}

int order_2_count[PROBLEM_RANGE] = {};
int quadratic_1_count[PROBLEM_RANGE] = {};
int quadratic_2_count[PROBLEM_RANGE] = {};
int quadratic_3_count[PROBLEM_RANGE] = {};
int quadratic_7_count[PROBLEM_RANGE] = {};
long long d[PROBLEM_RANGE] = {};

void InitPrimeFactorCount(long long offset)
{
    for (int i = 0; i < PROBLEM_RANGE; i++)
    {
        order_2_count[i] = 0;
        quadratic_1_count[i] = 0;
        quadratic_2_count[i] = 0;
        quadratic_3_count[i] = 0;
        quadratic_7_count[i] = 0;
        d[i] = offset + i;
    }

    long long mod8, mod7;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        long long base = primes[i];
        do 
        {
            long long j0 = (offset % base == 0) ? 0 : (base - (offset % base));
            for (long long j = j0; j < PROBLEM_RANGE; j += base)
            {
                d[j] /= primes[i];
                if (primes[i] == 2)
                {
                    order_2_count[j]++;
                }

                if (primes[i] % 4 == 3)
                {
                    quadratic_1_count[j]++;
                }
                
                mod8 = primes[i] % 8;
                if (mod8 == 5 || mod8 == 7)
                {
                    quadratic_2_count[j]++;
                }
                
                if (primes[i] % 3 == 2)
                {
                    quadratic_3_count[j]++;
                }
                
                mod7 = primes[i] % 7;
                if (mod7 == 3 || mod7 == 5 || mod7 == 6)
                {
                    quadratic_7_count[j]++;
                }
            }
            base *= primes[i];
        }
        while (base < PROBLEM_RANGE);
    }

    for (int i = 0; i < PROBLEM_RANGE; i++)
    {
        if (d[i] > 1)
        {
            if (d[i] % 4 == 3)
            {
                quadratic_1_count[i]++;
            }
                
            mod8 = d[i] % 8;
            if (mod8 == 5 || mod8 == 7)
            {
                quadratic_2_count[i]++;
            }
                
            if (d[i] % 3 == 2)
            {
                quadratic_3_count[i]++;
            }
                
            mod7 = d[i] % 7;
            if (mod7 == 3 || mod7 == 5 || mod7 == 6)
            {
                quadratic_7_count[i]++;
            }
        }
    }
    std::cout << "InitPrimeFactorCount completed!" << std::endl;
}

bool IsSumOfTwoPositiveSquares(long long n, long long d)
{
    long long t;
    for (long long i = 1; d*i*i <= n; i++)
    {
        t = n - d*i*i;
        if (t > 0)
        {
            long long r = (long long)(sqrt(double(t)) + 0.5);
            if (r > 0 && t == r*r)
            {
                return true;
            }
        }
    }
    return false;
}

void Solve()
{
    long long count = 0;
    for (long long i = 0; i < OFFSET_COUNT; i++)
    {
        long long offset = PROBLEM_RANGE * i;
        std::cout << "Current offset: " << offset << std::endl;
        InitPrimeFactorCount(offset);
        for (long long n = 0; n < PROBLEM_RANGE; n++)
        {
            if (order_2_count[n] % 2 == 0 && 
                quadratic_1_count[n] % 2 == 0 && 
                quadratic_2_count[n] % 2 == 0 &&
                quadratic_3_count[n] % 2 == 0 && 
                quadratic_7_count[n] % 2 == 0 &&
                IsSumOfTwoPositiveSquares(n + offset, 1) &&
                IsSumOfTwoPositiveSquares(n + offset, 2) &&
                IsSumOfTwoPositiveSquares(n + offset, 3) &&
                IsSumOfTwoPositiveSquares(n + offset, 7))
            {
                count++;
                if (count % 1000 == 0)
                {
                    std::cout << count << " =>> " << n + offset << std::endl;
                }
            }
        }
    }
    std::cout << count << std::endl;
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
