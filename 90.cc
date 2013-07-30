#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>

// http://stackoverflow.com/questions/5095407/n-choose-k-implementation
template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
    /* Credits: Thomas Draper */
    if (first == last || first == k || last == k)
    {
        return false;
    }
    Iterator first_ = first;
    Iterator last_ = last;
    ++first_;
    if (last == first_)
    {
        return false;
    }
    first_ = last;
    --first_;
    first_ = k;
    --last_;
    while (first != first_)
    {
        if (*--first_ < *last_)
        {
            Iterator j = k;
            while (!(*first_ < *j)) ++j;
            std::iter_swap(first_, j);
            ++first_;
            ++j;
            last_ = k;
            std::rotate(first_, j, last);
            while (last != j)
            {
                ++j;
                ++last_;
            }
            std::rotate(k, last_, last);
            return true;
        }
    }
    std::rotate(first, k, last);
    return false;
}

// -----------------------------------------------------------------------------

long long prime[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
std::map<std::string, long long> cube_hash;
std::vector<std::string> cubes;

long long MakeHash(const std::string& cube)
{
    long long hash = 1;
    for (std::string::const_iterator it = cube.begin(); it != cube.end(); it++)
    {
        hash *= prime[*it - '0'];
    }
    return hash;
}

void GenerateCubes()
{
    std::string digits = "0123456789";
    std::string cube;
    std::size_t faces = 6;
    do
    {
        cube = std::string(digits.begin(), digits.begin() + faces);
        cube_hash[cube] = MakeHash(cube);
        cubes.push_back(cube);
    }
    while (next_combination(digits.begin(), digits.begin() + faces, digits.end()));
}


bool IsPossible(const std::string& a, const std::string& b)
{
    long long hash_a = cube_hash[a];
    long long hash_b = cube_hash[b];

    // 01
    if (((hash_a % prime[0]) || (hash_b % prime[1])) &&
        ((hash_a % prime[1]) || (hash_b % prime[0])))
    {
        return false;
    }

    // 04
    if (((hash_a % prime[0]) || (hash_b % prime[4])) &&
        ((hash_a % prime[4]) || (hash_b % prime[0])))
    {
        return false;
    }

    // 09
    if (((hash_a % prime[0]) || (hash_b % prime[9])) &&
        ((hash_a % prime[9]) || (hash_b % prime[0])) &&
        ((hash_a % prime[0]) || (hash_b % prime[6])) &&
        ((hash_a % prime[6]) || (hash_b % prime[0])))
    {
        return false;
    }

    // 16
    if (((hash_a % prime[1]) || (hash_b % prime[6])) &&
        ((hash_a % prime[6]) || (hash_b % prime[1])) &&
        ((hash_a % prime[1]) || (hash_b % prime[9])) &&
        ((hash_a % prime[9]) || (hash_b % prime[1])))
    {
        return false;
    }

    // 25
    if (((hash_a % prime[2]) || (hash_b % prime[5])) &&
        ((hash_a % prime[5]) || (hash_b % prime[2])))
    {
        return false;
    }

    // 36
    if (((hash_a % prime[3]) || (hash_b % prime[6])) &&
        ((hash_a % prime[6]) || (hash_b % prime[3])) &&
        ((hash_a % prime[3]) || (hash_b % prime[9])) &&
        ((hash_a % prime[9]) || (hash_b % prime[3])))
    {
        return false;
    }

    // 49 & 64
    if (((hash_a % prime[4]) || (hash_b % prime[9])) &&
        ((hash_a % prime[9]) || (hash_b % prime[4])) &&
        ((hash_a % prime[4]) || (hash_b % prime[6])) &&
        ((hash_a % prime[6]) || (hash_b % prime[4])))
    {
        return false;
    }

    // 81
    if (((hash_a % prime[8]) || (hash_b % prime[1])) &&
        ((hash_a % prime[1]) || (hash_b % prime[8])))
    {
        return false;
    }

    return true;
}

void Solve()
{
    int count = 0;
    int num_cubes = cubes.size();
    for (int i = 0; i < num_cubes; i++)
    {
        for (int j = i; j < num_cubes; j++)
        {
            if (IsPossible(cubes[i], cubes[j]))
            {
                count++;
            }
        }
    }
    std::cout << count << std::endl;
}

int main(int argc, char* argv[])
{
    GenerateCubes();
    Solve();
    return 0;
}