#include <algorithm>
#include <iostream>
#include <set>
#include <stdio.h>

bool visited[47000] = {};
long long prime[4851] = {};

inline void InitPrimeTable()
{
    long long curr_pos = 0;
    for (long long i = 2; i < 47000; i++)
    {
        if (!visited[i])
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < 47000; j += i)
            {
                visited[j] = true;
            }
        }
    }
}

bool IsPrime(long long n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long i = 0; i < 4851 && (prime[i] * prime[i] <= n); i++)
    {
        if (n == prime[i])
        {
            return true;
        }
        if (n % prime[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

int digits[9] = {};

inline void InitDigits()
{
    for (int i = 0; i < 9; i++)
    {
        digits[i] = i+1;
    }
}

long long GetNumber(int start_pos, int end_pos)
{
    long long rv = 0;
    for (int i = start_pos; i < end_pos; i++)
    {
        rv *= 10;
        rv += digits[i];
    }
    return rv;
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    InitDigits();

    std::set<long long> set_rep;
    long long a[7] = {};
    do
    {
        if (digits[8] == 0)
        {
            continue;
        }

        for (int i = 1; i < 8; i++)
        {
            a[0] = GetNumber(0, i);
            if (!IsPrime(a[0]))
            {
                continue;
            }
            a[1] = GetNumber(i, 9);
            if (IsPrime(a[1]))
            {
                set_rep.insert(a[0] * a[1]);
            }
            for (int j = i+1; j < 8; j++)
            {
                a[1] = GetNumber(i, j);
                if (!IsPrime(a[1]))
                {
                    continue;
                }
                a[2] = GetNumber(j, 9);
                if (IsPrime(a[2]))
                {
                    set_rep.insert(a[0] * a[1] * a[2]);
                }
                for (int p = j+1; p < 8; p++)
                {
                    a[2] = GetNumber(j, p);
                    if (!IsPrime(a[2]))
                    {
                        continue;
                    }
                    a[3] = GetNumber(p, 9);
                    if (IsPrime(a[3]))
                    {
                        set_rep.insert(a[0] * a[1] * a[2] * a[3]);
                    }
                    for (int q = p+1; q < 8; q++)
                    {
                        a[3] = GetNumber(p, q);
                        if (!IsPrime(a[3]))
                        {
                            continue;
                        }
                        a[4] = GetNumber(q, 9);
                        if (IsPrime(a[4]))
                        {
                            set_rep.insert(a[0] * a[1] * a[2] * a[3] * a[4]);
                        }
                        for (int r = q+1; r < 8; r++)
                        {
                            a[4] = GetNumber(q, r);
                            if (!IsPrime(a[4]))
                            {
                                continue;
                            }
                            a[5] = GetNumber(r, 9);
                            if (IsPrime(a[5]))
                            {
                                set_rep.insert(a[0] * a[1] * a[2] * a[3] * a[4] * a[5]);
                            }
                            for (int s = r+1; s < 8; s++)
                            {
                                a[5] = GetNumber(r, s);
                                if (!IsPrime(a[5]))
                                {
                                    continue;
                                }
                                a[6] = GetNumber(s, 9);
                                if (IsPrime(a[6]))
                                {
                                    set_rep.insert(a[0] * a[1] * a[2] * a[3] * a[4] * a[5] * a[6]);
                                    std::cout << "It should not be here." << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    while (std::next_permutation(digits, digits+9));

    std::cout << set_rep.size() << std::endl;

    return 0;
}