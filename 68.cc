#include <algorithm>
#include <iostream>
#include <stdio.h>

#define EDGE (5)

int external_ring[EDGE] = {};
int internal_ring[EDGE] = {};

void InitRing()
{
    for (int i = 0; i < EDGE; i++)
    {
        internal_ring[i] = i+1;
        external_ring[i] = i+1+EDGE;
    }
}

bool IsMagicRing()
{
    int base_sum = external_ring[0] + internal_ring[0] + internal_ring[1];
    for (int i = 1; i < EDGE; i++)
    {
        if (external_ring[i] + internal_ring[i] + internal_ring[(i+1)%EDGE]
            != base_sum)
        {
            return false;
        }        
    }
    return true;
}

long long GetDigitString()
{
    long long rv = 0;
    for (int i = 0; i < EDGE; i++)
    {
        rv *= (external_ring[i] < 10) ? 10 : 100;
        rv += external_ring[i];
        rv *= 10;
        rv += internal_ring[i];
        rv *= 10;
        rv += internal_ring[(i+1)%EDGE];
    }
    return rv;
}

long long Solve()
{
    long long max = 0, curr;
    do 
    {
        do 
        {
            if (IsMagicRing())
            {
                curr = GetDigitString();
                if (curr > max)
                {
                    max = curr;
                }
            }
        }
        while (std::next_permutation(internal_ring, internal_ring + EDGE));
    }
    while (std::next_permutation(external_ring + 1, external_ring + EDGE));
    return max;
}

int main(int argc, char* argv[])
{
    InitRing();
    std::cout << Solve() << std::endl;
    return 0;
}