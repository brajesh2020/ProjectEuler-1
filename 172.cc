#include <iostream>
#include <stdio.h>

#define DIGIT_COUNT (18)

long long factorial[DIGIT_COUNT + 1];
long long solution_vector[10] = {};
long long total_count;

void InitFactorial()
{
    factorial[0] = 1;
    for (long long i = 1; i <= DIGIT_COUNT; i++)
    {
        factorial[i] = factorial[i-1] * i;
    }
}

bool IsValid(int dimension)
{
    long long sum = 0;
    for (int i = 0; i < dimension; i++)
    {
        sum += solution_vector[i];
    }
    if (dimension == 10)
    {
        return sum == DIGIT_COUNT;
    }
    return sum <= DIGIT_COUNT;
}

long long GetCount()
{
    long long count = factorial[DIGIT_COUNT];
    for (int i = 0; i < 10; i++)
    {
        count /= factorial[solution_vector[i]];
    }
    return count;
}

void Backtrack(int dimension)
{
    if (!IsValid(dimension))
    {
        return;
    }
    if (dimension == 10)
    {
        total_count += GetCount();
        return;
    }
    
    for (int i = 0; i <= 3; i++)
    {
        solution_vector[dimension] = i;
        Backtrack(dimension + 1);
    }
}

void Solve()
{
    InitFactorial();
    total_count = 0;
    Backtrack(0);
    std::cout << total_count / 10 * 9 << std::endl;
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}
