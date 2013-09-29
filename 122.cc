#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>

typedef std::vector<int> ExpList;

int M(int n)
{
    if (n == 1)
    {
        return 0;
    }

    std::queue<ExpList> exp_lists;
    ExpList first;
    first.push_back(1);
    exp_lists.push(first);
    while (!exp_lists.empty())
    {
        ExpList top = exp_lists.front();
        exp_lists.pop();
        int len = top.size();
        for (int i = 0; i < len; i++)
        {
            int sum = top[i] + top[len - 1];
            if (sum > n)
            {
                break;
            }
            else if (sum == n)
            {
                return len;
            }
            ExpList next(top);
            next.push_back(sum);
            exp_lists.push(next);
        }
    }
}

void Solve()
{
    int sum = 0;
    for (int n = 1; n <= 200; n++)
    {
        int m = M(n);
        sum += m;
        std::cout << n << " " << m << std::endl;
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}
