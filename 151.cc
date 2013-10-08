#include <iostream>
#include <map>
#include <set>
#include <stdio.h>

struct EnvelopeState
{
    int paper_sheets[4];

    EnvelopeState() 
    { 
        paper_sheets[0] = 0; 
        paper_sheets[1] = 0; 
        paper_sheets[2] = 0; 
        paper_sheets[3] = 0; 
    }

    EnvelopeState(int a2, int a3, int a4, int a5) 
    { 
        paper_sheets[0] = a2; 
        paper_sheets[1] = a3; 
        paper_sheets[2] = a4; 
        paper_sheets[3] = a5; 
    }

    EnvelopeState(const EnvelopeState& other) 
    { 
        paper_sheets[0] = other.paper_sheets[0];
        paper_sheets[1] = other.paper_sheets[1];
        paper_sheets[2] = other.paper_sheets[2];
        paper_sheets[3] = other.paper_sheets[3];
    }

    int GetCount() const 
    {
        int count = 0;
        for (int i = 0; i < 4; i++)
        {
            count += paper_sheets[i];
        }
        return count;
    }

    int GetSize() const 
    {
        int size = 0;
        for (int i = 0; i < 4; i++)
        {
            size += paper_sheets[i] * (1 << (3-i));
        }
        return size;
    }

    bool operator < (const EnvelopeState& other) const
    {
        for (int i = 0; i < 4; i++)
        {
            if (paper_sheets[i] != other.paper_sheets[i])
            {
                return paper_sheets[i] < other.paper_sheets[i];
            }
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    EnvelopeState init(1, 1, 1, 1);

    std::map<EnvelopeState, double> probability;
    probability[init] = 1.0;
    
    std::set<EnvelopeState> states;
    states.insert(init);
    for (int size = 15; size > 1; size--)
    {
        std::set<EnvelopeState> next_states;
        for (std::set<EnvelopeState>::iterator it = states.begin(); 
                it != states.end(); it++)
        {
            EnvelopeState top = *it;
            
            for (int i = 0; i < 4; i++)
            {
                if (top.paper_sheets[i] <= 0)
                {
                    continue;
                }
                EnvelopeState next_state(top);
                next_state.paper_sheets[i]--;
                for (int j = i + 1; j < 4; j++)
                {
                    next_state.paper_sheets[j]++;
                }
                
                if (probability.find(next_state) == probability.end())
                {
                    probability[next_state] = 0.0;
                }
                probability[next_state] += probability[top] 
                    * double(top.paper_sheets[i]) / double(top.GetCount());
                next_states.insert(next_state);
            }
        }
        states = next_states;
    }

    double expected_value = 0.0;
    for (std::map<EnvelopeState, double>::iterator it = probability.begin();
            it != probability.end(); it++)
    {
        if (it->first.GetCount() == 1 && it->first.GetSize() != 1)
        {
            expected_value += it->second;
            printf("Found: %d => %.6lf\n", it->first.GetSize(), it->second);
        }
    }
    printf("%.6lf\n", expected_value);
}
