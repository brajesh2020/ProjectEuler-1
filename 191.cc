#include <iostream>
#include <stdio.h>

#define DAYS (30)

long long T[DAYS][3] = {};

void InitConsecutiveAbsentTable()
{
    T[0][0] = 1;
    T[0][1] = 1;
    T[0][2] = 0;

    for (long long i = 1; i < DAYS; i++)
    {
        T[i][0] = T[i-1][0] + T[i-1][1] + T[i-1][2];
        T[i][1] = T[i-1][0];
        T[i][2] = T[i-1][1];
    }
}

long long GetCountWithZeroLateDay(int days)
{
    return T[days-1][0] + T[days-1][1] + T[days-1][2];
}

long long GetCountWithOneLateDay(int days)
{
    long long count = GetCountWithZeroLateDay(days - 1) * 2;
    for (int i = 1; i < days - 1; i++)
    {
        int j = days - 1 - i;
        count += GetCountWithZeroLateDay(i) * GetCountWithZeroLateDay(j);
    }
    return count;
}

int main(int argc, char* argv[])
{
    InitConsecutiveAbsentTable();
    std::cout << GetCountWithZeroLateDay(DAYS) + GetCountWithOneLateDay(DAYS) 
        << std::endl;
    return 0;
}