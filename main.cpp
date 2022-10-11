#include <bits/stdc++.h>
#include "constants.cpp"
#include "numsys.cpp"
#include "operations.cpp"
using namespace std;

string encrypt(string key, string full_text)
{
    string result = "";
    while (full_text.size() % 64 != 0)
    {
        full_text += "0";
    }
    for (int i = 0; i < full_text.size() / 64; i++)
    {
        string text = full_text.substr(64 * i, 64);
        cout << "text for " << i << " is " << bin2hex(text) << "\n";

        // apply perm_choice1 ➡️ DES effective key
        key = permute(key, perm_1, 56);
        // apply initial permutation
        text = permute(text, initial_prem, 64);
        // cout << "after initial permutation: " << bin2hex(text) << "\n";

        for (int j = 0; j < 16; j++)
        {
            text = DES_enc_round(j, key, text);
            // cout << "Round 1 " << bin2hex(text) << "\n";
        }
        text = text.substr(32) + text.substr(0, 32);
        text = permute(text, inv_initial_prem, 64);
        result += bin2hex(text);
    }
    return result;
}

int main(void)
{
    // string key = "0123456789ABCDEF";
    // string text = "123456789ABCDEF";
    // cout << encrypt(key, text);

    // string a = "10101010101010101010101010101010101010101010101010101010";
    // cout << DES_enc_round(1, a, a);

    string key = "6CA6CB20FF3C485F";
    string text = "58914751893458BABBABCCDDCCEFE41343144134";

    key = hex2bin(key);
    text = hex2bin(text);

    cout << encrypt(key, text) << "\n";
}