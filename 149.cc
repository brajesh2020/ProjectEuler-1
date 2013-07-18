#include <iostream>
#include <stdio.h>

long long M[2000][2000] = {};

int D[4][2] = { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, -1 } };

long long MaxSequence(int x, int y, int d)
{
    long long max_so_far = M[x][y], max_ending_here = M[x][y];
    int next_i, next_j;
    for (int i = 1; i < 2000; i++)
    {
        next_i = x + D[d][0] * i;
        next_j = y + D[d][1] * i;
        if (next_i < 0 || next_i >= 2000 || next_j < 0 || next_j >= 2000)
        {
            break;
        }
        if (max_ending_here < 0)
        {
            max_ending_here = M[next_i][next_j];
        }
        else
        {
            max_ending_here += M[next_i][next_j];
        }
        if (max_ending_here >= max_so_far)
        {
            max_so_far = max_ending_here;
        }
    }
    return max_so_far;
}

void InitMatrix()
{
    for (long long k = 1; k <= 55; k++)
    {
        M[(k-1)/2000][(k-1)%2000] = 
            ((100003 - 200003*k + 300007*k*k*k) % 1000000) - 500000;
    }
    for (long long k = 56; k <= 4000000; k++)
    {
        M[(k-1)/2000][(k-1)%2000] = ((M[(k-25)/2000][(k-25)%2000] + 
            M[(k-56)/2000][(k-56)%2000] + 1000000) % 1000000) - 500000;
    }
}

int main(int argc, char* argv[])
{
    InitMatrix();

    long long max = M[0][0];
    long long max_sequence;
    for (int pos = 0; pos < 2000; pos++)
    {
        max_sequence = MaxSequence(pos, 0, 0);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
        max_sequence = MaxSequence(0, pos, 1);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
        max_sequence = MaxSequence(pos, 0, 2);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
        max_sequence = MaxSequence(0, pos, 2);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
        max_sequence = MaxSequence(pos, 3, 3);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
        max_sequence = MaxSequence(3, pos, 3);
        if (max_sequence > max)
        {
            max = max_sequence;
        }
    }
    std::cout << max << std::endl;

    return 0;
}