#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <stdio.h>

#define SIEVE_RANGE (100000)
#define PRIME_COUNT (9592)
#define DIGIT_COUNT (10)

bool visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {}; 

void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

bool IsPrime(long long n) 
{
    for (long long i = 0; 
        (i < PRIME_COUNT) && (prime[i] * prime[i] <= n); i++) 
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

// -----------------------------------------------------------------------------

bool IsPrimeSet(int n, long long rep)
{
    std::string word = to_string<long long>(rep);
    if (word.size() != n)
    {
        return false;
    }
    std::sort(word.begin(), word.end());
    long long next;
    do
    {
        if (word[0] == '0')
        {
            continue;
        }
        next = to_type<long long>(word);
        if (IsPrime(next))
        {
            return true;
        }
    }
    while (std::next_permutation(word.begin(), word.end()));
    return false;
}

bool IsRepeated(int n, int d, int m)
{
    long long base = 0;
    for (int i = 0; i < m; i++)
    {
        base *= 10;
        base += d;
    }
    long long offset_range = 1;
    for (int i = 0; i < n - m; i++)
    {
        offset_range *= 10;
    }
    long long shift_range = 1;
    for (int i = 0; i < m; i++)
    {
        shift_range *= 10;
    }

    for (int i = 0; i < offset_range; i++)
    {
        if (IsPrimeSet(n, base + i * shift_range))
        {
            return true;
        }
    }
    return false;
}

long long M(int n, int d)
{
    for (int m = n; m > 0; m--)
    {
        if (IsRepeated(n, d, m))
        {
            return m;
        }
    }
    return 0;
}

// -----------------------------------------------------------------------------

long long S(int n, int d, int m)
{
    std::set<long long> primes;

    long long base = 0;
    for (int i = 0; i < m; i++)
    {
        base *= 10;
        base += d;
    }
    long long offset_range = 1;
    for (int i = 0; i < n - m; i++)
    {
        offset_range *= 10;
    }
    long long shift_range = 1;
    for (int i = 0; i < m; i++)
    {
        shift_range *= 10;
    }

    for (int i = 0; i < offset_range; i++)
    {
        std::string word = to_string<long long>(base + i * shift_range);
        if (word.size() != n)
        {
            continue;
        }
        std::sort(word.begin(), word.end());
        long long next;
        do
        {
            if (word[0] == '0')
            {
                continue;
            }
            next = to_type<long long>(word);
            if (IsPrime(next))
            {
                primes.insert(next);
            }
        }
        while (std::next_permutation(word.begin(), word.end()));
    }

    long long sum = 0;
    for (std::set<long long>::iterator it = primes.begin();
        it != primes.end(); it++)
    {
        sum += (*it);
    }
    return sum;
}

// -----------------------------------------------------------------------------

void Solve()
{
    long long sum = 0;
    for (int d = 0; d <= 9; d++)
    {
        long long m = M(DIGIT_COUNT, d);
        long long s = S(DIGIT_COUNT, d, m);
        sum += s;
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    Solve();
    return 0;
}