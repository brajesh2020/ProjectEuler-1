#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <stdio.h>

struct GameNode
{
    int status;
    int depth;
    std::string move_sequence;

    GameNode() : status(0), depth(0) { }

    static int GetStatusHash(const std::string& config)
    {
        int hash = 0;
        for (int i = 0; i < 16; i++)
        {
            if (config[i] == '_')
            {
                hash = hash | 1 << (i + 16);
                hash = hash & ~(1 << i);
            }
            else if (config[i] == 'R')
            {
                hash = hash | 1 << i;
            }
        }
        return hash;
    }

    void SetConfiguration(const std::string& config)
    {
        status = GetStatusHash(config);
    }

    bool MoveLeft()
    {
        int empty_pos = GetEmptyPos();
        if (empty_pos % 4 == 3)
        {
            return false;
        }
        MoveInternal(empty_pos, 1);
        depth++;
        move_sequence += "L";
        return true;
    }

    bool MoveRight()
    {
        int empty_pos = GetEmptyPos();
        if (empty_pos % 4 == 0)
        {
            return false;
        }
        MoveInternal(empty_pos, -1);
        depth++;
        move_sequence += "R";
        return true;
    }
    
    bool MoveUp()
    {
        int empty_pos = GetEmptyPos();
        if (empty_pos > 11)
        {
            return false;
        }
        MoveInternal(empty_pos, 4);
        depth++;
        move_sequence += "U";
        return true;
    }

    bool MoveDown()
    {
        int empty_pos = GetEmptyPos();
        if (empty_pos < 4)
        {
            return false;
        }
        MoveInternal(empty_pos, -4);
        depth++;
        move_sequence += "D";
        return true;
    }

    int GetEmptyPos()
    {
        for (int i = 0; i < 16; i++)
        {
            if (status & 1 << (i + 16))
            {
                return i;
            }
        }
        return -1;
    }

    void MoveInternal(int base, int shift)
    {
        status ^= (1 << (base + 16)) | (1 << (base + 16 + shift));
        if (status & 1 << (base + shift))
        {
            status = status | 1 << base;
        }
        else
        {
            status = status & ~(1 << base);
        }
        status = status & ~(1 << (base + shift));
    }
};

long long Checksum(const std::string& move_sequence)
{
    long long checksum = 0L;
    for (std::string::const_iterator it = move_sequence.begin();
        it != move_sequence.end(); it++)
    {
        checksum = (checksum * 243 + static_cast<long long>(*it)) % 100000007;
    }
    return checksum;
}

std::string Visit(const std::string& starting, const std::string& destination)
{
    GameNode node;
    node.SetConfiguration(starting);
    int destination_status = GameNode::GetStatusHash(destination);

    std::set<int> visited;
    std::queue<GameNode> bfs_queue;
    bfs_queue.push(node);

    while (bfs_queue.size() > 0)
    {
        GameNode top = bfs_queue.front();
        bfs_queue.pop();

        if (top.status == destination_status)
        {
            return top.move_sequence;
        }
        if (visited.find(top.status) != visited.end())
        {
            continue;
        }
        visited.insert(top.status);

        {
            GameNode next(top);
            if (next.MoveRight())
            {
                bfs_queue.push(next);
            }
        }

        {
            GameNode next(top);
            if (next.MoveLeft())
            {
                bfs_queue.push(next);
            }
        }

        {
            GameNode next(top);
            if (next.MoveDown())
            {
                bfs_queue.push(next);
            }
        }

        {
            GameNode next(top);
            if (next.MoveUp())
            {
                bfs_queue.push(next);
            }
        }
    }
    return std::string();
}

int main(int argc, char* argv[])
{
    std::string starting = 
        "_RBB"
        "RRBB"
        "RRBB"
        "RRBB";
    std::string destination = 
        "RRBB"
        "RBBB"
        "R_RB"
        "RRBB";
    std::string move_sequence = Visit(starting, destination);
    std::cout << move_sequence << " " << Checksum(move_sequence) << std::endl;

    destination = 
        "_BRB"
        "BRBR"
        "RBRB"
        "BRBR";
    move_sequence = Visit(starting, destination);
    std::cout << move_sequence << " " << Checksum(move_sequence) << std::endl;
    return 0;
}