#include <iostream>
#include <string>
#include <stdio.h>

struct Sudoku 
{
    int grid[9][9];

    bool Solve()
    {
        int row, col;
        if (!FindEmptyLocation(row, col))
        {
            return true;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (IsSafe(row, col, num))
            {
                grid[row][col] = num;
                if (Solve())
                {
                    return true;
                }
                grid[row][col] = 0;
            }
        }
        return false; 
    }

    bool FindEmptyLocation(int &row, int &col)
    {
        for (row = 0; row < 9; row++)
        {
            for (col = 0; col < 9; col++)
            {
                if (grid[row][col] == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool IsSafe(int row, int col, int num)
    {
        return !IsInRow(row, num) && !IsInCol(col, num) && 
            !IsInBox(row - row % 3 , col - col % 3, num);
    }

    bool IsInRow(int row, int num)
    {
        for (int col = 0; col < 9; col++)
        {
            if (grid[row][col] == num)
            {
                return true;
            }
        }
        return false;
    }

    bool IsInCol(int col, int num)
    {
        for (int row = 0; row < 9; row++)
        {
            if (grid[row][col] == num)
            {
                return true;
            }
        }
        return false;
    }

    bool IsInBox(int box_begin_row, int box_begin_col, int num)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (grid[row + box_begin_row][col + box_begin_col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }

    int GetSignature()
    {
        return grid[0][0] * 100 + grid[0][1] * 10 + grid[0][2];
    }

    void Debug()
    {
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                printf("%2d", grid[row][col]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
};

int main()
{
    Sudoku sudoku;
    int rv = 0;
    std::string buffer;
    while (getline(std::cin, buffer))
    {
        for (int row = 0; row < 9; row++)
        {
            getline(std::cin, buffer);
            for (int col = 0; col < 9; col++)
            {
                sudoku.grid[row][col] = buffer[col] - '0';
            }
        }
        sudoku.Solve();
        rv += sudoku.GetSignature();
    }
    std::cout << rv << std::endl;
    return 0;
}