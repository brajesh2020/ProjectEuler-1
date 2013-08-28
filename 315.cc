#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

#define LOWER_BOUND (10000000)
#define SIEVE_RANGE (20000000)
#define PRIME_COUNT (606028)

bool visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {}; 
int digit_rep[10][7] = 
{
    { 1, 1, 1, 0, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 1, 0 },
    { 1, 0, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 1, 1 },
    { 0, 1, 1, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 0, 1, 1 },
};
int digit_line_segments[10] = {};
int smart_transition[10][10] = {};

template <class T>
inline std::string to_string(const T& t)
{
    std::stringstream builder;
    builder << t;
    return builder.str();
}

void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!visited[i]) 
        {
            if (i > LOWER_BOUND)
            {
                primes[curr_pos] = i;
                curr_pos++;
            }
            for (long long j = i + i; j < SIEVE_RANGE; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

// -----------------------------------------------------------------------------

void InitDigitLineSegments()
{
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            digit_line_segments[i] += digit_rep[i][j];
        }
    }
}

void InitSmartTransitionTable()
{
    for (int i = 0; i <= 9; i++)
    {
        for (int j = i + 1; j <= 9; j++)
        {
            int same_count = 0;
            for (int k = 0; k < 7; k++)
            {
                if (digit_rep[i][k] == 1 && digit_rep[j][k] == 1)
                {
                    same_count++;
                }
            }
            smart_transition[i][j] = digit_line_segments[i] + 
                digit_line_segments[j] - 2 * same_count;
            smart_transition[j][i] = smart_transition[i][j];
        }
    }
}

// -----------------------------------------------------------------------------

long long GetDigitSum(long long n)
{
    if (n < 10)
    {
        return n;
    }
    long sum = 0;
    long long d = n;
    while (d)
    {
        sum += (d % 10);
        d /= 10;
    }
    return sum;
}

long long GetLightSegmentCount(long long n)
{
    if (n < 10)
    {
        return digit_line_segments[n];
    }
    long long count = 0;
    long long d = n;
    while (d)
    {
        count += digit_line_segments[d % 10];
        d /= 10;
    }
    return count;
}

long long GetSamClockTransitionCount(long long n)
{
    long long count = 0;
    long long d = n;
    while (d >= 10)
    {
        count += GetLightSegmentCount(d);
        d = GetDigitSum(d);
    }
    count += GetLightSegmentCount(d);
    return count * 2;
}

// -----------------------------------------------------------------------------

long long GetSmartLightSegmentCount(long long start, long long end)
{
    std::string start_str = to_string<long long>(start);
    std::string end_str = to_string<long long>(end);
    int start_digit_count = start_str.size();
    int end_digit_count = end_str.size();
    int offset = start_digit_count - end_digit_count;
    long long count = 0;
    for (int i = 0; i < offset; i++)
    {
        count += digit_line_segments[start_str[i] - '0'];
    }
    for (int i = offset; i < start_digit_count; i++)
    {
        count += smart_transition[start_str[i] - '0'][end_str[i - offset] - '0'];
    }
    return count;
}

long long GetMaxClockTransitionCount(long long n)
{
    long long d = n;
    long long next;
    long long count = GetLightSegmentCount(d);
    while (d >= 10)
    {
        next = GetDigitSum(d);
        count += GetSmartLightSegmentCount(d, next);
        d = next;
    }
    count += GetLightSegmentCount(d);
    return count;
}

void Solve()
{
    long long diff = 0;
    for (int i = 0; i < PRIME_COUNT; i++)
    {
        diff = diff + GetSamClockTransitionCount(primes[i]) - 
            GetMaxClockTransitionCount(primes[i]);
    }
    std::cout << diff << std::endl;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitDigitLineSegments();
    InitSmartTransitionTable();
    Solve();
    return 0;
}