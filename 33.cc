#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[])
{
    for (int i = 10; i < 100; i++)
    {
        for (int j = i+1; j < 100; j++)
        {
            int i_digit[2] = { i/10, i%10 };
            int j_digit[2] = { j/10, j%10 };

            if (i_digit[0] == j_digit[1])
            {
                if (i * j_digit[0] == j * i_digit[1])
                {
                    printf("%d/%d = %d/%d\n", i, j, i_digit[1], j_digit[0]);
                }
            }
            else if (i_digit[1] == j_digit[0])
            {
                if (i * j_digit[1] == j * i_digit[0])
                {
                    printf("%d/%d = %d/%d\n", i, j, i_digit[0], j_digit[1]);
                }
            }
        }
    }
    return 0;
}