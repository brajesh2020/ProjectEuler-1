#include <iostream>
#include <stdio.h>

#define N (5)

bool is_used[1 << N] = {};
int solution_vector[1 << N] = {};

bool IsValid(int dimension)
{
    if (dimension == 1)
    {
        return true;
    }
    else if (dimension == (1 << N))
    {
        for (int i = 0; i < (1 << N); i++)
        {
            if (solution_vector[i] % (1 << (N-1)) != 
                solution_vector[(i+1)%(1 << N)] >> 1)
            {
                return false;
            }
        }
    }
    else 
    {
        for (int i = 0; i < dimension - 1; i++)
        {
            if (solution_vector[i] % (1 << (N-1)) != 
                solution_vector[i+1] >> 1)
            {
                return false;
            }
        }
    }
    return true;
}

void DebugSolutionVector()
{
    for (int i = 0; i < N; i++)
    {
        printf("0");
    }
    for (int i = 1; i < (1 << N) - N + 1; i++)
    {
        printf("%d", solution_vector[i] % 2);
    }
    printf("\n");
}

long long GetSolutionVectorRep()
{
    long long rep = 0;
    for (int i = 1; i < (1 << N) - N + 1; i++)
    {
        rep *= 2;
        rep += solution_vector[i] % 2;
    }
    return rep;
}

long long S = 0;

void Backtrack(int dimension)
{
    if (!IsValid(dimension))
    {
        return;
    }
    if (dimension == (1 << N))
    {
        S += GetSolutionVectorRep();
        return;
    }
    for (int i = 1; i < (1 << N); i++)
    {
        if (!is_used[i])
        {
            solution_vector[dimension] = i;
            is_used[i] = true;
            Backtrack(dimension + 1);
            is_used[i] = false;
        }
    }
}

int main(int argc, char* argv[])
{
    solution_vector[0] = 0;
    is_used[0] = true;
    Backtrack(1);
    std::cout << S << std::endl;
    return 0;
}
