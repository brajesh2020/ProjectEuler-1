#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>

#define N (32)
#define M (10)
#define PATTERN_COUNT (3329)

int solution_vector[20] = {};
int bricks[2] = { 2, 3 };
std::vector< std::set<int> > patterns;
bool cracked[PATTERN_COUNT][PATTERN_COUNT] = {};

void InsertPattern(int dimension)
{
    std::set<int> rep;
    int length = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        length += solution_vector[i];
        rep.insert(length);
    }
    patterns.push_back(rep);
}

int GetLength(int dimension)
{
    int length = 0;
    for (int i = 0; i < dimension; i++)
    {
        length += solution_vector[i];
    }
    return length;
}

void DebugSolutionVector(int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        printf("%d ", solution_vector[i]);
    }
    printf("\n");
}

void Backtrack(int dimension)
{
    int length = GetLength(dimension);
    if (length > N)
    {
        return;
    }
    if (length == N)
    {
        InsertPattern(dimension);
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        solution_vector[dimension] = bricks[i];
        Backtrack(dimension + 1);
    }
}

bool IsCracked(int i, int j)
{
    for (std::set<int>::iterator p = patterns[i].begin();
        p != patterns[i].end(); p++)
    {
        if (patterns[j].find(*p) != patterns[j].end())
        {
            return true;
        }
    }
    return false;
}

void InitCrackedMap()
{
    for (int i = 0; i < PATTERN_COUNT; i++)
    {
        for (int j = i; j < PATTERN_COUNT; j++)
        {
            cracked[i][j] = cracked[j][i] = IsCracked(i, j);
        }
    }
}

long long GetWays(long long layers)
{
    long long prev_ways[PATTERN_COUNT] = {};
    long long curr_ways[PATTERN_COUNT] = {};
    for (int j = 0; j < PATTERN_COUNT; j++)
    {
        prev_ways[j] = 1;
        curr_ways[j] = 1;
    }
    for (int i = 1; i < layers; i++)
    {
        for (int j = 0; j < PATTERN_COUNT; j++)
        {
            curr_ways[j] = 0;
            for (int k = 0; k < PATTERN_COUNT; k++)
            {
                if (!cracked[j][k])
                {
                    curr_ways[j] += prev_ways[k];
                }
            }
        }
        for (int j = 0; j < PATTERN_COUNT; j++)
        {
            prev_ways[j] = curr_ways[j];
        }
    }

    long long total_ways = 0;
    for (int j = 0; j < PATTERN_COUNT; j++)
    {
        total_ways += curr_ways[j];
    }
    return total_ways;
}

void Solve()
{
    Backtrack(0);
    InitCrackedMap();
    std::cout << GetWays(M) << std::endl;
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}
