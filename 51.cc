#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

template <class T>
inline std::string to_string(const T& t) {
    std::stringstream builder;
    builder << t;
    return builder.str();
}

template <class T>
inline T to_type(const std::string& s) {
    std::stringstream builder(s);
    T t;
    builder >> t;
    return t;
}

// -----------------------------------------------------------------------------

#define SIEVE_RANGE (1000002)
#define PRIME_COUNT (78498)

bool sieve[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {};

inline void InitPrimeTable()
{
    sieve[0] = sieve[1] = true;
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve[j] = true;
            }
        }
    }
}

// -----------------------------------------------------------------------------

void ReplacePlaces()
{
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        std::string curr_string = to_string<long long>(prime[i]);
        std::string next_string;
        long long next;
        long long count;
        for (int r = 0; r < curr_string.size(); r++)
        {
            for (int s = r+1; s < curr_string.size(); s++)
            {
                if (curr_string[r] != curr_string[s])
                {
                    continue;
                }
                for (int t = s+1; t < curr_string.size(); t++)
                {
                    if (curr_string[s] != curr_string[t])
                    {
                        continue;
                    }
                    count = 0;
                    for (int digit = 0; digit <= 9; digit++)
                    {
                        next_string = curr_string;
                        next_string[r] = digit + '0';
                        next_string[s] = digit + '0';
                        next_string[t] = digit + '0';
                        
                        if (next_string[0] == '0')
                        {
                            continue;
                        }
                        next = to_type<long long>(next_string);

                        if (next < SIEVE_RANGE && !sieve[next])
                        {
                            count++;
                        }
                    }
                    if (count == 8)
                    {
                        std::cout << prime[i] << std::endl;
                        return;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    ReplacePlaces();
    return 0;
}