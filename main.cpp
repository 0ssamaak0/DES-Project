#include <bits/stdc++.h>
#include "operations.cpp"
#include "constants.cpp"
using namespace std;

string encrypt(string key, string text)
{
    string result = "";

    // apply perm_choice1 ➡️ DES effective key
    key = permute(key, perm_1, 56);
    // apply initial permutation
    text = permute(text, initial_prem, 64);
    return "";
}

int main(void)
{
    // string key = "0123456789ABCDEF";
    // string text = "123456789ABCDEF";
    // cout << encrypt(key, text);

    string a = "1010101010101010101010101010";
    cout << shift_left(a, 1) << "\n";
}