#include <iostream>
#include <map>
#include <set>
#include <stdio.h>

inline long long Norm(long long a)
{
    return (a < 0) ? -a : a;
}

long long GCD(long long a, long long b) 
{
    a = Norm(a);
    b = Norm(b);
    while (b) 
    {
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

    Fraction() : n(0), d(1) { }
    Fraction(long long init_n, long long init_d) : n(init_n), d(init_d) { }

    static Fraction Inverse(const Fraction& f)
    {
        Fraction rv(f.d, f.n);
        rv.Normalize();
        return rv;
    }

    static Fraction RegularSum(const Fraction& a, const Fraction& b)
    {
        Fraction rv(a.n*b.d + b.n*a.d, a.d*b.d);
        rv.Normalize();
        return rv;
    }

    static Fraction HarmonicSum(const Fraction& a, const Fraction& b)
    {
        return Inverse(RegularSum(Inverse(a), Inverse(b)));
    }

    void Normalize()
    {
        long long gcd = GCD(n, d);
        n /= gcd;
        d /= gcd;

        if (d < 0)
        {
            n *= -1;
            d *= -1;
        }
    }

    void Debug() const
    {
        printf("%lld/%lld\n", n, d);
    }

    bool operator < (const Fraction& other) const
    {
        return n * other.d < other.n * d;
    }
};

// -----------------------------------------------------------------------------

std::map< int, std::set<Fraction> > d;
std::set<Fraction> total;

void InitNumOfTotalCapacitanceValues()
{
    d[1].insert(Fraction(1, 1));
    total.insert(Fraction(1, 1));
    std::cout << total.size() << std::endl;

    for (int i = 2; i <= 18; i++)
    {
        for (int j = 1; j <= i/2; j++)
        {
            for (std::set<Fraction>::iterator outer_it = d[j].begin();
                outer_it != d[j].end(); outer_it++)
            {
                for (std::set<Fraction>::iterator inner_it = d[i-j].begin();
                    inner_it != d[i-j].end(); inner_it++)
                {
                    d[i].insert(Fraction::RegularSum(*outer_it, *inner_it));
                    d[i].insert(Fraction::HarmonicSum(*outer_it, *inner_it));
                    total.insert(Fraction::RegularSum(*outer_it, *inner_it));
                    total.insert(Fraction::HarmonicSum(*outer_it, *inner_it));
                }
            }
        }
        std::cout << total.size() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    InitNumOfTotalCapacitanceValues();
    return 0;
}