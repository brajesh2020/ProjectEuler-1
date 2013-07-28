#include <iostream>
#include <stdio.h>

#define MAX (50)

struct Point
{
    long long x;
    long long y;

    Point() : x(0), y(0) { }
    Point(long long init_x, long long init_y) : x(init_x), y(init_y) { }

    void Set(long long init_x, long long init_y)
    {
        x = init_x;
        y = init_y;
    }

    long long Dot(const Point& other) const
    {
        return x * other.x + y * other.y;
    }

    Point Minus(const Point& other) const
    {
        return Point(x - other.x, y - other.y);
    }
};

long long GetCount(long long n)
{
    long long count = n * n;
    long long limit = (n+1)*(n+1);
    for (long long i = 1; i < limit; i++)
    {
        for (long long j = 1; j < limit; j++)
        {
            Point a(i%(n+1), i/(n+1));
            Point b(j%(n+1), j/(n+1));
            if (i != j && a.Dot(b.Minus(a)) == 0)
            {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    std::cout << GetCount(MAX) << std::endl;
    return 0;
}