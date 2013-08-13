#include <iostream>
#include <set>
#include <stdio.h>

#define DIGIT_COUNT (20)

std::set<long long> squares;
long long solution_vector[10] = {};
long long factorial[DIGIT_COUNT + 1];

void InitSquares()
{
    for (long long i = 1; i <= 40; i++)
    {
        squares.insert(i*i);
    }
}

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
    long long digit_count = 0;
    for (int i = 0; i < dimension; i++)
    {
        digit_count += solution_vector[i];
    }

    if (dimension < 10)
    {
        return digit_count <= DIGIT_COUNT;
    }
    return digit_count == DIGIT_COUNT;
}

long long total_digit_sum = 0;

void Process()
{
    long long sum = 0;
    for (int i = 1; i < 10; i++)
    {
        sum = sum + solution_vector[i] * i * i;
    }
    if (squares.find(sum) == squares.end())
    {
        return;
    }
    long long permutation_count = factorial[DIGIT_COUNT];
    long long digit_sum = 0;
    for (int i = 0; i < 10; i++)
    {
        permutation_count /= factorial[solution_vector[i]];
        digit_sum += solution_vector[i] * i;
    }
    total_digit_sum += digit_sum * permutation_count / DIGIT_COUNT;
    total_digit_sum %= 1000000000;
    std::cout << total_digit_sum << std::endl;
}

void Backtrack(int dimension)
{
    if (!IsValid(dimension))
    {
        return;
    }
    if (dimension == 10)
    {
        Process();
        return;
    }
    for (int i = 0; i <= DIGIT_COUNT; i++)
    {
        solution_vector[dimension] = i;
        Backtrack(dimension + 1);
    }
}

void Solve()
{
    InitSquares();
    InitFactorial();
    Backtrack(0);

    long long r = total_digit_sum;
    long long final[10] = {};
    for (int i = 0; i < 9; i++)
    {
        final[i] = r % 10;
        r /= 10;
        r += total_digit_sum;
    }
    for (int i = 8; i >= 0; i--)
    {
        std::cout << final[i];
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}
