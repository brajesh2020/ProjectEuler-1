#include <iostream>
#include <stdio.h>

bool is_used[10] = {};
int solution_vector[10] = {};

long long GetTotal(int dice_count)
{
    long long total = 0;
    for (int i = 0; i < dice_count; i++)
    {
        total += solution_vector[i];
    }
    return total;
}

long long total_map[37] = {};
void Backtrack(int dimension, int face_count, int dice_count)
{
    if (dimension == dice_count)
    {
        total_map[GetTotal(dice_count)]++;
        return;
    }
    for (int i = 1; i <= face_count; i++)
    {
        solution_vector[dimension] = i;
        is_used[dimension] = true;
        Backtrack(dimension + 1, face_count, dice_count);
        is_used[dimension] = false;
    }
}

long long pyramidal_total_map[37] = {};
long long cubic_total_map[37] = {};
long long acc_pyramidal_total_map[37] = {};
long long acc_cubic_total_map[37] = {};

void InitPyramidalTotalMap()
{
    for (int i = 0; i <= 36; i++)
    {
        total_map[i] = 0;
    }
    Backtrack(0, 4, 9);
    for (int i = 0; i <= 36; i++)
    {
        pyramidal_total_map[i] = total_map[i];
    }
    for (int i = 1; i <= 36; i++)
    {
        acc_pyramidal_total_map[i] = 
            acc_pyramidal_total_map[i-1] + pyramidal_total_map[i];
    }
}

void InitCubicTotalMap()
{
    for (int i = 0; i <= 36; i++)
    {
        total_map[i] = 0;
    }
    Backtrack(0, 6, 6);
    for (int i = 0; i <= 36; i++)
    {
        cubic_total_map[i] = total_map[i];
    }
    for (int i = 1; i <= 36; i++)
    {
        acc_cubic_total_map[i] = 
            acc_cubic_total_map[i-1] + cubic_total_map[i];
    }
}

int main(int argc, char* argv[])
{
    InitPyramidalTotalMap();
    InitCubicTotalMap();

    long long universal_event = 
        acc_pyramidal_total_map[36] * acc_cubic_total_map[36]; 
    long long winning_event = 0;
    for (int i = 1; i <= 36; i++)
    {
        winning_event += (pyramidal_total_map[i] * acc_cubic_total_map[i-1]);
    }
    printf("%.7lf\n", double(winning_event)/double(universal_event));

    return 0;
}
