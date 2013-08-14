#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

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

template <class T>
inline T to_type(const std::string& s)
{
    std::stringstream builder(s);
    T t;
    builder >> t;
    return t;
}

template <class T>
std::vector<T> Split(const std::string& buffer, const std::string& delimiter)
{
    std::vector<T> rv;
    size_t start = 0, end = 0;
    while (end != std::string::npos)
    {
        end = buffer.find(delimiter, start);
        rv.push_back(to_type<T>(buffer.substr(start, 
            (end == std::string::npos) ? std::string::npos : end - start)));
        start = ((end > (std::string::npos - delimiter.size())) ? 
            std::string::npos : end + delimiter.size());
    }
    return rv;
}

// -----------------------------------------------------------------------------

std::vector<int> sum_vector;
std::vector<int> order_vector;

void InitVectors(const std::vector<int>& v)
{
    sum_vector.clear();
    order_vector.clear();
    int subset_count = 1 << v.size();
    for (int i = 1; i < subset_count; i++)
    {
        int sum = 0;
        int order = 0;
        for (int j = 0; j < v.size(); j++)
        {
            if ((1 << j) & i)
            {
                sum += v[j];
                order++;
            }
        }
        sum_vector.push_back(sum);
        order_vector.push_back(order);
    }
}

bool HasPropertyOne()
{
    std::set<int> sum_set = to_set<int>(sum_vector);
    return sum_vector.size() == sum_set.size();
}

bool HasPropertyTwo()
{
    int len = sum_vector.size();
    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if (order_vector[i] > order_vector[j] && 
                sum_vector[i] < sum_vector[j])
            {
                return false;
            }
            if (order_vector[i] < order_vector[j] && 
                sum_vector[i] > sum_vector[j])
            {
                return false;
            }
        }
    }
    return true;
}

int S(const std::vector<int>& v)
{
    InitVectors(v);
    int sum = 0;
    if (HasPropertyOne() && HasPropertyTwo())
    {
        for (std::vector<int>::const_iterator it = v.begin(); 
            it != v.end(); it++)
        {
            sum += (*it);
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    int total_sum = 0, sum;
    std::string buffer;
    while (getline(std::cin, buffer))
    {
        sum = S(Split<int>(buffer, ","));
        if (sum > 0)
        {
            std::cout << buffer << " => " << sum << std::endl;
        }
        total_sum += sum;
    }
    std::cout << total_sum << std::endl;
    return 0;
}