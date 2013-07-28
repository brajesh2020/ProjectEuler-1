#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <stdio.h>

std::map<char, int> numerals;
std::map<char, int> precedence;

void Init()
{
    char rep[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    int value[7] = { 1, 5, 10, 50, 100, 500, 1000 };
    for (int i = 0; i < 7; i++)
    {
        numerals[rep[i]] = value[i];
        precedence[rep[i]] = i;
    }
}

int GetValue(const std::string& rep)
{
    int rv = 0;
    int prev_precedence = 999, curr_precedence;
    int prev_value, curr_value;
    for (int i = 0; i < rep.size(); i++)
    {
        curr_precedence = precedence[rep[i]];
        curr_value = numerals[rep[i]];
        if (prev_precedence >= curr_precedence)
        {
            rv = rv + curr_value;
        }
        else
        {
            rv = rv + curr_value - 2 * prev_value;
        }
        prev_precedence = curr_precedence;
        prev_value = curr_value;
    }
    return rv; 
}

std::string GetRep(int value)
{
    std::stringstream builder;
    int n = value;
    int digit = n/1000;
    for (int i = 0; i < digit; i++)
    {
        builder << "M";
    }
    n %= 1000;
    digit = n/100;
    if (digit == 9)
    {
        builder << "CM";
    }
    else if (digit == 4)
    {
        builder << "CD";
    }
    else 
    {
        if (digit >= 5)
        {
            builder << "D";
            digit -= 5;
        }
        for (int i = 0; i < digit; i++)
        {
            builder << "C";
        }
    }
    n %= 100;
    digit = n/10;
    if (digit == 9)
    {
        builder << "XC";
    }
    else if (digit == 4)
    {
        builder << "XL";
    }
    else 
    {
        if (digit >= 5)
        {
            builder << "L";
            digit -= 5;
        }
        for (int i = 0; i < digit; i++)
        {
            builder << "X";
        }
    }
    digit = n % 10;
    if (digit == 9)
    {
        builder << "IX";
    }
    else if (digit == 4)
    {
        builder << "IV";
    }
    else 
    {
        if (digit >= 5)
        {
            builder << "V";
            digit -= 5;
        }
        for (int i = 0; i < digit; i++)
        {
            builder << "I";
        }
    }
    return builder.str();
}

int main(int argc, char* argv[])
{
    Init();
    int before_count = 0;
    int after_count = 0;
    std::string rep;
    while (std::cin >> rep)
    {
        before_count += rep.size();
        after_count += GetRep(GetValue(rep)).size();
    }
    std::cout << (before_count - after_count) << std::endl;
    return 0;
}