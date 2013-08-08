#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

std::set< std::set<int> > subsets;

void GenerateNonEmptySubsets(std::set<int> universal) 
{
    if (universal.empty()) 
    {
        return;
    }
    subsets.insert(universal);
    for (std::set<int>::iterator it = universal.begin(); 
        it != universal.end(); it++)
    {
        std::set<int> next(universal);
        next.erase(next.find(*it));
        GenerateNonEmptySubsets(next);
    }
}

// -----------------------------------------------------------------------------

int GetSum(const std::set<int>& s)
{
    int sum = 0;
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        sum += (*it);
    }
    return sum;
}

// -----------------------------------------------------------------------------

template <class T>
inline std::vector< T > to_vector(const std::set< T >& t)
{
    std::vector< T > v;
    for (std::set< T >::const_iterator it = t.begin(); it != t.end(); it++)
    {
        v.push_back(*it);
    }
    return v;
}

template <class T>
inline std::set< T > to_set(const std::vector< T >& t)
{
    std::set< T > s;
    for (std::vector< T >::const_iterator it = t.begin(); it != t.end(); it++)
    {
        s.insert(*it);
    }
    return s;
}

// -----------------------------------------------------------------------------

std::vector< std::set<int> > subset_vector;
std::vector<int> sum_vector;
std::vector<int> size_vector;

bool HasPropertyOne()
{
    std::set<int> sum_set = to_set<int>(sum_vector);
    return sum_vector.size() == sum_set.size();
}

bool HasPropertyTwo()
{
    int len = subset_vector.size();
    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if ((size_vector[i] > size_vector[j]) && 
                (sum_vector[i] <= sum_vector[j]))
            {
                return false;
            }
        }
    }
    return true;
}

bool IsSpecialSumSet(std::set<int> universal)
{
    subsets.clear();
    GenerateNonEmptySubsets(universal);

    subset_vector = to_vector< std::set<int> >(subsets);
    sum_vector.clear();
    for (std::vector< std::set<int> >::iterator it = subset_vector.begin(); 
        it != subset_vector.end(); it++)
    {
        sum_vector.push_back(GetSum(*it));
        size_vector.push_back(it->size());
    }

    return HasPropertyOne() && HasPropertyTwo();
}

void Debug(const std::set<int>& s)
{
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); it++)
    {
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;
}

void Solve()
{
    int elements[7] = { 20, 31, 38, 39, 40, 42, 45 };
    std::set<int> test_set;
    for (int i = 0; i < 7; i++)
    {
        test_set.insert(elements[i]);
    }
    if (IsSpecialSumSet(test_set))
    {
        Debug(test_set);
    }
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}