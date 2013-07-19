#include <iostream>
#include <string>
#include <stdio.h>

#define N (40)
#define MAX_COST (999999)

int cost[N][N];
bool visited[N];

void InitCost()
{
    std::string buffer;
    for (int i = 0; i < N; i++)
    {
        getline(std::cin, buffer);
        int number = 0;
        int pos = 0;
        for (int j = 0; j < buffer.size(); j++)
        {
            char c = buffer[j];
            if (c >= '0' && c <= '9')
            {
                number *= 10;
                number += c - '0';
            }
            else if (c == '-')
            {
                number = MAX_COST;
            }
            else 
            {
                cost[i][pos] = number;
                number = 0;
                pos++;
            }
        }
        cost[i][pos] = number;
    }
}

int GetTotalCost()
{
    int total_cost = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (cost[i][j] < MAX_COST)
            {
                total_cost += cost[i][j];
            }
        }
    }
    return total_cost / 2;
}

int GetMinCost()
{
    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
    }
    visited[0] = true;

    int min_cost = 0;
    int num_edges = 0;
    while (num_edges < N - 1) 
    {
        int min = MAX_COST;
        int x = 0; 
        int y = 0;
        for (int i = 0; i < N; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < N; j++)
                {
                    if (!visited[j])
                    {
                        if (min > cost[i][j])
                        {
                            min = cost[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        visited[y] = true;
        min_cost += min;
        num_edges++;
    }

    return min_cost;
}

int main(int argc, char* argv[])
{
    InitCost();
    std::cout << GetTotalCost() - GetMinCost() << std::endl;
    return 0;
}