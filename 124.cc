#include <algorithm>
#include <iostream>
#include <stdio.h>

struct RadicalOrder
{
    long long n_;
    long long rad_;
    bool operator < (const RadicalOrder& other) const 
    {
        if (rad_ != other.rad_)
        {
            return rad_ < other.rad_;
        }
        return n_ < other.n_;
    }
};

RadicalOrder E[100001];

void InitE()
{
    for (long long i = 0; i < 100001; i++)
    {
        E[i].n_ = i;
        E[i].rad_ = 1;
    }
    for (long long i = 2; i < 100001; i++)
    {
        if (E[i].rad_ == 1)
        {
            for (long long j = i; j < 100001; j += i)
            {
                E[j].rad_ *= i;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitE();
    std::sort(E+1, E+100001);
    std::cout << E[10000].n_ << std::endl;
    return 0;
}