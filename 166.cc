#include <iostream>
#include <stdio.h>

#define EMPTY_LOCATION (-100)

struct CrissCross 
{
    int grid_[4][4];
    int sum_;
    long long solution_count_;

    void Init(int sum)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                grid_[row][col] = EMPTY_LOCATION;
            }
        }
        sum_ = sum;
        solution_count_ = 0;
    }

    void Solve()
    {
        int row, col;
        if (!FindEmptyLocation(row, col))
        {
            solution_count_++;
            return;
        }

        for (int num = 0; num <= 9; num++)
        {
            if (IsSafe(row, col, num))
            {
                grid_[row][col] = num;
                Solve();
                grid_[row][col] = EMPTY_LOCATION;
            }
        }
    }

    long long GetSolutionCount() const { return solution_count_; }

    bool FindEmptyLocation(int &row, int &col) const
    {
        for (row = 0; row < 4; row++)
        {
            for (col = 0; col < 4; col++)
            {
                if (grid_[row][col] == EMPTY_LOCATION)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool IsSafe(int row, int col, int num) const
    {
        return IsSafeRow(row, col, num) && IsSafeCol(row, col, num) &&
            IsSafeDiagonal(row, col, num);
    }

    bool IsSafeRow(int row, int col, int num) const
    {
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {    
            sum += (j == col) ? num : grid_[row][j];
        }
        if (sum < 0)
        {
            return true;
        }
        return sum == sum_;
    }

    bool IsSafeCol(int row, int col, int num) const
    {
        int sum = 0;
        for (int i = 0; i < 4; i++)
        {    
            sum += (i == row) ? num : grid_[i][col];
        }
        if (sum < 0)
        {
            return true;
        }
        return sum == sum_;
    }

    bool IsSafeDiagonal(int row, int col, int num) const
    {
        if (row == col)
        {
            int sum = 0;
            for (int i = 0; i < 4; i++)
            {    
                sum += (i == row) ? num : grid_[i][i];
            }
            if (sum < 0)
            {
                return true;
            }
            return sum == sum_;
        }
        if (row + col == 3)
        {
            int sum = 0;
            for (int i = 0; i < 4; i++)
            {    
                sum += (i == row) ? num : grid_[i][3 - i];
            }
            if (sum < 0)
            {
                return true;
            }
            return sum == sum_;
        }
        return true;
    }
};

int main()
{
    long long total_count = 0;
    CrissCross criss_cross;
    for (int i = 0; i <= 36; i++)
    {
        criss_cross.Init(i);
        criss_cross.Solve();
        total_count += criss_cross.GetSolutionCount();
        std::cout << criss_cross.GetSolutionCount() << std::endl;
    }
    std::cout << total_count << std::endl;
    return 0;
}