#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

long long Norm(long long a)
{
    return (a < 0) ? -a : a;
}

// Euclidean Algorithm
long long GCD(long long a, long long b) {
    a = Norm(a);
    b = Norm(b);
    while (b) {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

struct Fraction
{
    long long n;
    long long d;

    Fraction(): n(0), d(1) { }
    Fraction(long long init_n): n(init_n), d(1) { }
    Fraction(long long init_n, long long init_d): n(init_n), d(init_d) 
    { 
        Normalize();
    }

    static Fraction Add(const Fraction& a, const Fraction& b)
    {
        return Fraction(a.n * b.d + b.n * a.d, a.d * b.d);
    }

    static Fraction Minus(const Fraction& a, const Fraction& b)
    {
        return Fraction(a.n * b.d - b.n * a.d, a.d * b.d);
    }
    
    static Fraction Multiply(const Fraction& a, const Fraction& b)
    {
        return Fraction(a.n * b.n, a.d * b.d);
    }

    static Fraction Divide(const Fraction& a, const Fraction& b)
    {
        return Fraction(a.n * b.d, a.d * b.n);
    }

    void Normalize()
    {
        long long gcd = GCD(n, d);
        if (gcd)
        {
            n /= gcd;
            d /= gcd;
        }
    }

    void Debug()
    {
        printf("Fraction: %lld/%lld\n", n, d);
    }
};

long long GetLongestSet(long long *n)
{
    std::set<long long> targets;
    do
    {
        std::vector<Fraction> results; 
        results.push_back(Fraction(n[0]));

        for (int i = 1; i < 4; i++)
        {
            Fraction f = Fraction(n[i]);
            std::vector<Fraction> internal_results;
            for (std::vector<Fraction>::iterator it = results.begin();
                it != results.end(); it++)
            {
                internal_results.push_back(Fraction::Add(*it, f));
                internal_results.push_back(Fraction::Minus(*it, f));
                internal_results.push_back(Fraction::Minus(f, *it));
                internal_results.push_back(Fraction::Multiply(*it, f));
                internal_results.push_back(Fraction::Divide(*it, f));
                internal_results.push_back(Fraction::Divide(f, *it));
            }
            results = internal_results;
        }

        for (std::vector<Fraction>::iterator it = results.begin();
            it != results.end(); it++)
        {
            if (it->d == 1 && it->n > 0)
            {
                targets.insert(it->n);
            }
        }
    }
    while (std::next_permutation(n, n+4));

    long long longest = 0;
    while (targets.find(longest + 1) != targets.end())
    {
        longest++;
    }
    return longest;
}

int main(int argc, char* argv[])
{
    long long rv = 0;
    for (long long a = 1; a <= 9; a++)
    {
        for (long long b = a+1; b <= 9; b++)
        {
            for (long long c = b+1; c <= 9; c++)
            {
                for (long long d = c+1; d <= 9; d++)
                {
                    long long n[4] = { a, b, c, d };
                    long long longest = GetLongestSet(n);
                    if (longest > rv)
                    {
                        rv = longest;
                        std::cout << a << b << c << d << " => " << 
                            longest << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}