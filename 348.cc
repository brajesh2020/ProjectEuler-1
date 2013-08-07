#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <stdio.h>

#define UPPER_BOUND (800000000)
#define LOWER_BOUND (500000000)

template <class T>
inline std::string to_string(const T& t)
{
    std::stringstream builder;
    builder << t;
    return builder.str();
}

bool IsPalindromic(long long number)
{
    std::string word = to_string<long long>(number);
    int length = word.size();
    for (int i = 0; i < length/2; i++)
    {
        if (word[i] != word[length-1-i])
        {
            return false;
        }
    }
    return true;
}

std::map<long long, int> rep_ways;

void InitRepWays()
{
    long long square;
    long long cube;
    long long sum;
    for (long long i = 2; ; i++)
    {
        square = i*i;
        if (square > UPPER_BOUND)
        {
            break;
        }
        for (long long j = 2; ; j++)
        {
            cube = j*j*j;
            sum = cube + square;
            if (sum < LOWER_BOUND)
            {
                continue;
            }
            if (sum > UPPER_BOUND)
            {
                break;
            }
            if (IsPalindromic(sum))
            {
                rep_ways[sum]++;
            }
        }
    }
}

void Solve()
{
    for (std::map<long long, int>::iterator it = rep_ways.begin();
        it != rep_ways.end(); it++)
    {
        if (it->second == 4)
        {
            std::cout << (it->first) << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    InitRepWays();
    Solve();
    return 0;
}