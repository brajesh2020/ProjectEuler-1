#include <iostream>
#include <stdio.h>

#define N (1000000)

int parent[N];
int rank[N];
int group_size[N];

void InitNetwork() 
{ 
    for (int i = 0; i < N; i++) 
    {
        parent[i] = i;
        rank[i] = 0;
        group_size[i] = 1;
    }
}

int FindSet(int x) 
{
    if (x != parent[x]) 
    {
        parent[x] = FindSet(parent[x]);
    }
    return parent[x];
}

int GetGroupSize(int x) 
{ 
    return group_size[FindSet(x)]; 
} 

void Link(int x, int y) 
{
    if (x == y) 
    {
        return;
    }
    if (rank[x] > rank[y]) 
    {
        parent[y] = x;
        group_size[x] += group_size[y];
        group_size[y] = 0;
    } 
    else 
    {
        parent[x] = y;
        group_size[y] += group_size[x];
        group_size[x] = 0;
        if (rank[x] == rank[y]) 
        {
            rank[y]++;
        }
    }
}

void Union(int x, int y) 
{
    Link(FindSet(x), FindSet(y));
}

void Solve()
{
    InitNetwork();

    int S[55] = {};
    int dial_count = 0;
    bool is_caller = true;
    int caller_number;
    for (long long k = 1; k <= 55; k++)
    {
        S[k-1] = (100003 - 200003*k + 300007*k*k*k) % 1000000;
        if (S[k-1] < 0)
        {
            S[k-1] += 1000000;
        }

        if (is_caller)
        {
            caller_number = S[k-1];
        }
        else if (caller_number != S[k-1])
        {
            Union(caller_number, S[k-1]);
            dial_count++;
        }
        is_caller = !is_caller;
    }
    
    long long k0;
    for (long long k = 56; ; k++)
    {
        k0 = (k-1) % 55;
        S[k0] = (S[(k-25)%55] + S[(k-56)%55]) % 1000000;

        if (is_caller)
        {
            caller_number = S[k0];
        }
        else if (caller_number != S[k0])
        {
            Union(caller_number, S[k0]);
            dial_count++;
        }
        is_caller = !is_caller;

        if (GetGroupSize(524287) >= 990000)
        {
            std::cout << dial_count << std::endl;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}