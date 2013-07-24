#include <iostream>
#include <vector>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int max_cycle_len = 1;
    for (int d = 2; d < 1000; d++)
    {
        std::vector<int> r_seq;
        int r_seq_len = 0;
        int pos;
        int q = 10;
        int r;
        do
        {
            r = q % d;
            for (pos = 0; pos < r_seq_len && r_seq[pos] != r; pos++);
            if (pos != r_seq_len)
            {
                break;
            }
            else
            {    
                r_seq.push_back(r);
                r_seq_len++;
            }
            q = r * 10;
        }
        while (r);

        if (r_seq_len - pos > max_cycle_len)
        {
            max_cycle_len = r_seq_len - pos;
        }
    }

    std::cout << max_cycle_len << std::endl;
    return 0;
}
