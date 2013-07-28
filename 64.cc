#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

int Norm(int a) 
{
    return (a < 0) ? -a : a;
}

// Euclidean Algorithm
int GCD(int a, int b) 
{
    a = Norm(a);
    b = Norm(b);
    while (b) 
    {
        int t = b;
        b = a % t;
        a = t;
    }
    return a;
}

// -----------------------------------------------------------------------------

std::set<int> squares;

void InitSquareSet()
{
    for (int i = 1; i <= 100; i++)
    {
        squares.insert(i*i);
    }
}

struct Fraction
{
    int D; 
    int a;
    int b;
    int c;
    int integer_part;

    Fraction(int n, int n_irrational_part, int n_rational_part, int d_part)
        : D(n), a(n_irrational_part), b(n_rational_part), c(d_part)
    {}

    void MakeProperFraction()
    {
        integer_part = GetIntegerPart();
        b -= c * integer_part; 
    }

    void Inverse()
    {
        int temp = c;
        c = D*a*a - b*b;
        a *= temp;
        b *= -temp;

        int gcd = GCD(GCD(a, b), c);
        c /= gcd;
        a /= gcd;
        b /= gcd;
    }

    bool operator < (const Fraction& other) const
    {
        if (a != other.a)
        {
            return a < other.a;
        }
        if (b != other.b)
        {
            return b < other.b;
        }
        return c < other.c;
    }

    int GetIntegerPart()
    {
        int x = 0;
        for (; a*a*D >= (c*x + c - b)*(c*x + c- b); x++);
        return x;
    }
};

struct RepBuilder
{
    RepBuilder(int n) : D(n)
    {
        Fraction f(n, 1, 0, 1);
        f.MakeProperFraction();
        integer_part = f.integer_part;

        std::set<Fraction> internal_fractions;
        for (int i = 0; ; i++)
        {
            f.Inverse();
            f.MakeProperFraction();
            cycle.push_back(f.integer_part);
            if (internal_fractions.find(f) == internal_fractions.end())
            {
                internal_fractions.insert(f);
            }
            else
            {
                cycle.pop_back();
                break;
            }
        }
    }

    void Debug()
    {
        printf("Sqrt[%d] = [%d;(", D, integer_part);
        int cycle_len = cycle.size();
        for (int i = 0; i < cycle_len; i++)
        {
            printf("%d", cycle[i]);
            if (i != cycle_len - 1)
            {
                printf(",");
            }
        }
        printf(")], period = %d\n", cycle_len);
    }

    int D;
    int integer_part;
    std::vector<int> cycle;
};

int main(int argc, char* argv[])
{
    InitSquareSet();
    int odd_cycle_count = 0;
    for (int D = 2; D <= 10000; D++)
    {
        if (squares.find(D) == squares.end())
        {
            RepBuilder builder(D); 
            if (builder.cycle.size() % 2)
            {
                odd_cycle_count++;
            }
            builder.Debug();
        }
    }
    std::cout << odd_cycle_count << std::endl;
    return 0;
}