#include <iostream>
#include <set>
#include <stack>
#include <stdio.h>

#define SIEVE_RANGE (5100000)
#define PRIME_COUNT (354971)
#define PROBLEM_RANGE (36100000)

bool sieve_visited[SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

void Sieve()
{
    long long curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            primes[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
}

bool problem_sieve[PROBLEM_RANGE] = {};
long long offset;

void InitProblemSieve(long long row)
{
    offset = (row - 2) * (row - 3)/2 + 1;
    long long problem_range = row * 5;
    for (long long i = 0; i < problem_range; i++)
    {
        problem_sieve[i] = false;
    }

    for (long long i = 0; i < PRIME_COUNT; i++)
    {
        long long p = primes[i];
        long long j0 = (offset % p == 0) ? 0 : (p - (offset % p));
        if (j0 + offset != p)
        {
            problem_sieve[j0] = true;
        }
        for (long long j = j0 + p; j < problem_range; j += p)
        {
            problem_sieve[j] = true;
        }
    }
}

inline bool IsPrime(long long n)
{
    return !problem_sieve[n - offset];
}

// -----------------------------------------------------------------------------

struct Node
{
    long long col;
    long long row;

    Node(long long init_col, long long init_row) 
        : col(init_col), row(init_row) { }

    bool IsValid() const 
    {
        return col >= 0 && row >= col;
    }

    bool IsPrimeNode() const 
    {
        if (!IsValid())
        {
            return false;
        }
        long long n = row * (row + 1)/2 + col + 1;
        return IsPrime(n);
    }

    long long GetNumber() const 
    {
        return IsValid() ? row * (row + 1)/2 + col + 1 : 0;
    }
};

bool IsPrimeTriplet(long long col, long long row)
{
    std::set< std::pair<long long, long long> > visited;

    std::stack<Node> dfs_stack;
    dfs_stack.push(Node(col, row));

    int count = 0;
    while (dfs_stack.size() > 0)
    {
        Node top = dfs_stack.top();
        dfs_stack.pop();
        
        if (!top.IsValid())
        {
            continue;
        }
        std::pair<long long, long long> rep = std::make_pair(top.col, top.row);
        if (visited.find(rep) != visited.end())
        {
            continue;
        }
        visited.insert(rep);
        if (!top.IsPrimeNode())
        {
            continue;
        }

        count++;
        if (count == 3)
        {
            return true;
        }

        for (long long dx = -1; dx <= 1; dx++)
        {
            for (long long dy = -1; dy <= 1; dy++)
            {
                dfs_stack.push(Node(top.col + dx, top.row + dy));
            }
        }
    }

    return false;
}

long long S(long long row)
{
    InitProblemSieve(row);
    long long row0 = row - 1;
    long long sum = 0;
    for (long long col = 0; col <= row0; col++)
    {
        if (IsPrimeTriplet(col, row0))
        {
            long long n = Node(col, row0).GetNumber();
            sum += n;
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    Sieve();
    std::cout << S(5678027) + S(7208785) << std::endl;
    return 0;
}
