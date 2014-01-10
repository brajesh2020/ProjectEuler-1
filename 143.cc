#include <iostream>
#include <map>
#include <set>
#include <stdio.h>

//#define BOUND (784LL)
#define BOUND (120000LL)

typedef std::set< long long > AdjacencyListType;
typedef std::map< long long, AdjacencyListType > GraphType;

std::set<long long> square_set;
GraphType graph;

long long GCD(long long a, long long b) 
{
    while (b) 
    {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

void InitSquareSet()
{
    long long bound = 3 * BOUND * BOUND;
    for (long long i = 1; i*i <= bound; i++)
    {
        square_set.insert(i*i);
    }
    std::cout << "InitSquareSet() finished" << std::endl;
}

void BuildGraph()
{
    for (long long i = 1; i <= BOUND; i++)
    {
        for (long long j = i; j <= BOUND; j++)
        {
            if (i + j > BOUND) 
            {
                break;
            }
            if (GCD(i, j) > 1)
            {
                continue;
            }
            long long d_square = i*i + i*j + j*j;
            if (square_set.find(d_square) != square_set.end())
            {
                std::cout << i << " " << j << " => " << d_square << std::endl;
                for (long long factor = 1; (i + j) * factor < BOUND; factor++)
                {
                    graph[i * factor].insert(j * factor);
                    graph[j * factor].insert(i * factor);
                }
            }
        }
    }
    std::cout << "BuildGraph() finished" << std::endl;
}

void Solve()
{
    std::set<long long> distance_set;
    for (GraphType::iterator it = graph.begin(); it != graph.end(); it++)
    {
        long long p = it->first;
        AdjacencyListType p_adjacent = it->second;
        for (AdjacencyListType::iterator i = p_adjacent.begin(); 
                i != p_adjacent.end(); i++)
        {
            long long q = *i;
            if (p > q) 
            {
                continue;
            }
            AdjacencyListType q_adjacent = graph[q];
            for (AdjacencyListType::iterator j = q_adjacent.begin(); 
                    j != q_adjacent.end(); j++)
            {
                long long r = *j;
                if (q > r)
                {
                    continue;
                }
                if (graph[r].find(p) == graph[r].end())
                {
                    continue;
                }
                long long distance = p+q+r;
                if (distance <= BOUND)
                {
                    distance_set.insert(distance);
                    std::cout << p << " <-> " << q << " <-> " << r << " : " 
                            << p+q+r << std::endl;
                }
            }
        }
    }

    long long sum = 0;
    for (std::set<long long>::iterator it = distance_set.begin(); 
            it != distance_set.end(); it++)
    {
        sum += (*it);
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[]) 
{
    InitSquareSet();
    BuildGraph();
    Solve();
    return 0;
}