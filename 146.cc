#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (150000000)
#define PRIME_COUNT (8444396)

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

long long GetSum(long long upper_bound)
{
    long long sum = 0;
    long long mod7, mod13;
    long long m;
    for (long long n = 10; n < upper_bound; n += 10)
    {
        mod7 = n % 7;
        mod13 = n % 13;
        if (n % 3 == 0 || (mod7 != 3 && mod7 != 4) || 
            mod13 == 0 || mod13 == 5 || mod13 == 6 || mod13 == 7 || mod13 == 8)
        {
            continue;
        }
        m = n*n;
        if (IsPrime(m+1) && IsPrime(m+3) && IsPrime(m+7) && 
            IsPrime(m+9) && IsPrime(m+13) && IsPrime(m+27))
        {
            std::cout << "Found: " << n << std::endl;
            sum += n;
        }
    }
    return sum;
}

long long Verify()
{
    long long candidates[] = 
    {
        10,
        315410,
        927070,
        2525870,
        8146100,
        16755190,
        39313460,
        97387280,
        119571820,
        121288430,
        130116970,
        139985660,
        144774340, 
    };

    long long sum = 0;
    for (int i = 0; i < sizeof(candidates)/sizeof(long long); i++)
    {
        long long m = candidates[i] * candidates[i];
        bool is_good = true;
        for (long long d = 2; d < 27; d++)
        {
            if (d == 3 || d == 7 || d == 9 || d == 13)
            {
                continue;
            }
            if (IsPrime(m+d))
            {
                is_good = false;
                break;
            }
        }
        if (is_good)
        {
            sum += candidates[i];
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    Sieve();
    // std::cout << "Sum: " << GetSum(150000000) << std::endl;
    std::cout << Verify() << std::endl;
    return 0;
}
