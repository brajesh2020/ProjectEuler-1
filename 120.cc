#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

std::vector<long long> pn_r_cycle;
std::vector<long long> qn_r_cycle;
std::set<long long> pn_r;
std::set<long long> qn_r;

long long max_r(long long a)
{
    long long mod = a*a;
    long long p = a-1;
    long long q = a+1;
    long long pn = 1;
    long long qn = 1;

    pn_r.clear();
    pn_r_cycle.clear();
    while (1)
    {    
        pn = (pn * p) % mod;
        if (pn_r.find(pn) != pn_r.end())
        {
            break;
        }
        pn_r.insert(pn);
        pn_r_cycle.push_back(pn);
    };

    qn_r.clear();
    qn_r_cycle.clear();
    while (1)
    {    
        qn = (qn * q) % mod;
        if (qn_r.find(qn) != qn_r.end())
        {
            break;
        }
        qn_r.insert(qn);
        qn_r_cycle.push_back(qn);
    };
    
    long long max = 2;
    long long sum;
    long long pn_r_cycle_len = pn_r_cycle.size();
    long long qn_r_cycle_len = qn_r_cycle.size();
    long long cycle_len = pn_r_cycle_len * qn_r_cycle_len;
    for (int i = 0; i < cycle_len; i++)
    {
        sum = (pn_r_cycle[i % pn_r_cycle_len] + 
            qn_r_cycle[i % qn_r_cycle_len]) % mod;
        if (sum > max)
        {
            max = sum;
        }
    }
    return max;
}

int main(int argc, char* argv[])
{
    long long sum = 0;
    long long curr_max_r;
    for (long long a = 3; a <= 1000; a++)
    {
        curr_max_r = max_r(a);
        sum += curr_max_r;
        std::cout << a << " => " << curr_max_r << std::endl;
    }
    std::cout << sum << std::endl;

    return 0;
}