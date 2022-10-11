#include <iostream>
#include <string>
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
        // cout << "text for " << i << " is " << bin2hex(text) << "\n";

        // apply perm_choice1 ➡️ DES effective key
        string key_perm_1 = permute(key, perm_1, 56);
        // apply initial permutation
        text = permute(text, initial_prem, 64);
        // cout << "after initial permutation: " << bin2hex(text) << "\n";

        for (int j = 0; j < 16; j++)
        {
            text = DES_enc_round(j, key_perm_1, text);
            // cout << "Round 1 " << bin2hex(text) << "\n";
        }
        // output of the last round here
        // output is swaped next
        text = text.substr(32) + text.substr(0, 32);
        // inverse permutation next
        text = permute(text, inv_initial_prem, 64);
        result += bin2hex(text);
    }
    return result;
}

string decrypt(string key, string full_text)
{
    string result = "";
    while (full_text.size() % 64 != 0)
    {
        full_text += "0";
    }
    for (int i = 0; i < full_text.size() / 64; i++)
    {
        string text = full_text.substr(64 * i, 64);
        // cout << "text for " << i << " is " << bin2hex(text) << "\n";

        // apply perm_choice1 ➡️ DES effective key
        string key_perm_1 = permute(key, perm_1, 56);
        // apply inverse initial permutation on cipher
        text = permute(text, initial_prem, 64);
        // apply swap 
        text = text.substr(32) + text.substr(0, 32);
        // cout << "after initial permutation: " << bin2hex(text) << "\n";

        for (int j = 15; j >= 0; j--)
        {
            text = DES_dec_round(j, key_perm_1, text);
            // cout << "Round 1 " << bin2hex(text) << "\n";
        }
        //text = text.substr(32) + text.substr(0, 32);
        text = permute(text, inv_initial_prem, 64);
        result += bin2hex(text);
    }
    return result;
}

int main(void)
{
    string key = "5B0C1DA0F12AF1F2";
    string text = "AC7526025FF6F849";
            
    key = hex2bin(key);
    text = hex2bin(text);
    cout << encrypt(key,text) << '\n';

    key = "5B0C1DA0F12AF1F2";
    string cipher = "5AC79DDEDFDE9587";
    key = hex2bin(key);
    cipher = hex2bin(cipher);
    //cout << encrypt(key,text) << '\n';
    cout << decrypt(key, cipher) << "\n";
}