#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

#define SIEVE_RANGE (26033)
#define PRIME_COUNT (2864)
#define N (5)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

// Shrink SIEVE_RANGE from 1000000 to 26033
// 1035037 => 3 7 823 121441 912763
// 446041 => 3 7 19237 83023 343771
// 423841 => 3 7 51133 96181 276517
// 330973 => 3 31 4159 17209 309571
// 200149 => 3 37 67 5923 194119
// 98003 => 3 3119 9887 36263 48731
// 76501 => 3 5323 10357 29587 31231
// 34427 => 7 1237 2341 12409 18433
// 26033 => 13 5197 5701 6733 8389
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
}

bool IsPrime(long long n) 
{
    for (long long i = 0; 
        (i < PRIME_COUNT) && (primes[i] * primes[i] <= n); i++) 
    {
        if (n == primes[i]) 
        {
            return true;
        }
        if (n % primes[i] == 0) 
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

template <class T>
inline std::string to_string(const T& t)
{
    std::stringstream builder;
    builder << t;
    return builder.str();
}

template <class T>
inline T to_type(const std::string& s)
{
    std::stringstream builder(s);
    T t;
    builder >> t;
    return t;
}

long long solution_vector[N] = {};
long long min_sum = SIEVE_RANGE + 1;

long long GetSum(int dimension)
{
    long long sum = 0;
    for (int i = 0; i < dimension; i++)
    {
        sum += solution_vector[i];
    }
    return sum;
}

bool IsValid(int dimension)
{
    if (GetSum(dimension) >= min_sum)
    {
        return false;
    }
    long long n;
    for (int i = 0; i < dimension; i++)
    {
        for (int j = i+1; j < dimension; j++)
        {
            n = to_type<long long>(
                to_string<long long>(solution_vector[i]) +
                to_string<long long>(solution_vector[j]));
            if (!IsPrime(n))
            {
                return false;
            }

            n = to_type<long long>(
                to_string<long long>(solution_vector[j]) +
                to_string<long long>(solution_vector[i]));
            if (!IsPrime(n))
            {
                return false;
            }
        }
    }
    return true;
}

void DebugSolutionVector(int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        printf("%d ", solution_vector[i]);
    }
    printf("\n");
}

void Backtrack(int dimension)
{
    if (!IsValid(dimension))
    {
        return;
    }
    if (dimension == N)
    {
        min_sum = GetSum(dimension);
        std::cout << min_sum << " => ";
        DebugSolutionVector(dimension);
        return;
    }
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        if (dimension == 0 || solution_vector[dimension-1] < primes[i])
        {
            solution_vector[dimension] = primes[i];
            Backtrack(dimension + 1);
        }
    }
}

void Solve()
{
    Backtrack(0);
}

int main(int argc, char* argv[])
{
    Sieve();
    Solve();
    return 0;
}
