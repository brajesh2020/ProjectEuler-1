#include <iostream>
#include <stack>
#include <stdio.h>

int polygonal_pos[6] = {};
int polygonal[6][90] = {};

void InitPolygonal()
{
    int p;

    // Triangle
    for (int i = 1; ; i++)
    {
        p = i*(i+1)/2;
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[0][polygonal_pos[0]] = p;
        polygonal_pos[0]++;
    }

    // Square
    for (int i = 1; ; i++)
    {
        p = i*i;
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[1][polygonal_pos[1]] = p;
        polygonal_pos[1]++;
    }

    // Pentagonal
    for (int i = 1; ; i++)
    {
        p = i*(3*i-1)/2;
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[2][polygonal_pos[2]] = p;
        polygonal_pos[2]++;
    }

    // Hexagonal
    for (int i = 1; ; i++)
    {
        p = i*(2*i-1);
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[3][polygonal_pos[3]] = p;
        polygonal_pos[3]++;
    }

    // Heptagonal
    for (int i = 1; ; i++)
    {
        p = i*(5*i-3)/2;
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[4][polygonal_pos[4]] = p;
        polygonal_pos[4]++;
    }

    // Octagonal
    for (int i = 1; ; i++)
    {
        p = i*(3*i-2);
        if (p < 1000)
        {
            continue;
        }
        if (p > 10000)
        {
            break;
        }
        if ((p/10) % 10 == 0)
        {
            continue;
        }
        polygonal[5][polygonal_pos[5]] = p;
        polygonal_pos[5]++;
    }
}

struct Node 
{
    bool visited_side[6];
    int pos;
    int p[6];

    Node() : pos(0)
    {
        for (int i = 0; i < 6; i++)
        {
            visited_side[i] = false;
            p[i] = 0;
        }
    }

    Node(int n, int side)
    {
        for (int i = 0; i < 6; i++)
        {
            visited_side[i] = false;
            p[i] = 0;
        }        
        visited_side[side] = true;
        p[0] = n;
        pos = 1;
    }

    Node(const Node& other) 
    {
        for (int i = 0; i < 6; i++)
        {
            visited_side[i] = other.visited_side[i];
            p[i] = other.p[i];
        }
        pos = other.pos;
    }

    bool IsValid() const
    {
        for (int i = 0; i < pos - 1; i++)
        {
            if (p[i] % 100 != p[i+1] / 100)
            {
                return false;
            }
        }
        if (pos == 6)
        {
            if (p[5] % 100 != p[0] / 100)
            {
                return false;
            }
        }
        return true;
    }

    bool IsFound() const
    {
        return pos == 6;
    }

    int Sum() const 
    {
        int sum = 0;
        for (int i = 0; i < pos; i++)
        {
            sum += p[i];
        }
        return sum;
    }
};

int Visit()
{
    std::stack<Node> dfs_stack;
    for (int j = 0; j < polygonal_pos[5]; j++)
    {
        dfs_stack.push(Node(polygonal[5][j], 5));
    }

    while (dfs_stack.size() > 0)
    {
        Node top = dfs_stack.top();
        dfs_stack.pop();

        if (!top.IsValid())
        {
            continue;
        }
        if (top.IsFound())
        {
            return top.Sum();
        }
        for (int i = 0; i < 6; i++)
        {
            if (top.visited_side[i])
            {
                continue;
            }

            for (int j = 0; j < polygonal_pos[i]; j++)
            {
                Node next(top);
                next.visited_side[i] = true;
                next.p[next.pos] = polygonal[i][j];
                next.pos++;
                dfs_stack.push(next);
            }
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
    InitPolygonal();
    std::cout << Visit() << std::endl;
    return 0;
}