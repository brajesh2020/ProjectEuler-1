#include <algorithm>
#include <iostream>
#include <stdio.h>

int digit[10] = {};

int main(int argc, char* argv[])
{
    for (int i = 0; i < 10; i++)
    {
        digit[i] = i;
    }
    int pos = 1;
    do 
    {
        if (pos == 1000000)
        {
            for (int i = 0; i < 10; i++)
            {
                printf("%d", digit[i]);
            }
            putchar('\n');
            break;
        }
        pos++;
    } 
    while (std::next_permutation(digit, digit+10));       
    return 0;
}