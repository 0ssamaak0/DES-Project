#include <bits/stdc++.h>
using namespace std;

string permute(string s, int *per_matrix, int size)
{
    string result = "";
    for (int i = 0; i < size; i++)
    {
        result += s[per_matrix[i] - 1];
    }
    return result;
}

string shift_left(string s, int num_shifts)
{
    string result = "";
    // for each shift
    for (int i = 0; i < num_shifts; i++)
    {
        // shift
        for (int j = 1; j < 28; j++)
        {
            result += s[j];
        }
        // append the first digit
        result += s[0];
        // prepare for the next shift if any
        s = result;
        result = "";
    }
    return result;
}

string round(int round_num, string key, string text)
{
}