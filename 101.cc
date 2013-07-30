#include <iostream>
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

    void Multiply(const Fraction& other)
    {
        n *= other.n;
        d *= other.d;
        Normalize();
    }

    void Multiply(long long other)
    {
        n *= other;
        Normalize();
    }

    void Add(const const Fraction& other)
    {
        n = n*other.d + other.n*d;
        d = d*other.d;
        Normalize();
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
};

// -----------------------------------------------------------------------------

long long u[10] = {};

void InitGeneratingFunction()
{
    for (int i = 0; i < 10; i++)
    {
        long long base = i+1;
        long long power = 1;
        for (int j = 0; j < 11; j++)
        {
            power *= base;
        }
        u[i] = (1 + power)/(1 + base);
    }
}

Fraction EvaluateLagrangeBasisPolynomial(int k, int jth)
{
    Fraction value(1, 1);
    for (int m = 1; m <= k; m++)
    {
        if (m != jth)
        {
            value.Multiply(Fraction(k + 1 - m, jth - m));
        }
    }
    return value;
}

long long GetBOP(int k)
{
    Fraction value(0, 1);
    for (int j = 1; j <= k; j++)
    {
        Fraction basis = EvaluateLagrangeBasisPolynomial(k, j);
        basis.Multiply(u[j-1]);
        value.Add(basis);
    }
    return (value.d == 1) ? value.n : -1;
}

int main(int argc, char* argv[])
{
    InitGeneratingFunction();
    long long rv = 0;
    for (int k = 1; k <= 10; k++)
    {
        rv += GetBOP(k);
    }
    std::cout << rv << std::endl;
    return 0;
}