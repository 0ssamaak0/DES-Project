#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "constants.cpp"
#include "numsys.cpp"
#include "operations.cpp"

using namespace std;
using namespace std::chrono;

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
        string key_perm1 = permute(key, perm_1, 56);

        // apply initial permutation
        text = permute(text, initial_prem, 64);
        // cout << "text after initial permutation: " << bin2hex(text) << "\n";

        for (int j = 0; j < 16; j++)
        {
            text = DES_enc_round(j, key_perm1, text);
            // cout << "Round " << j << " " << bin2hex(text) << "\n";
        }
        // output of the last round here
        // output is swaped next
        text = text.substr(32) + text.substr(0, 32);
        // inverse permutation next
        // cout << "text before inv initial permutation: " << bin2hex(text) << "\n";
        text = permute(text, inv_initial_prem, 64);
        // cout << "text after inv initial permutation: " << bin2hex(text) << "\n";
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
        string key_perm1 = permute(key, perm_1, 56);

        // apply inverse initial permutation on cipher
        text = permute(text, initial_prem, 64);
        text = text.substr(32) + text.substr(0, 32);

        for (int j = 15; j >= 0; j--)
        {
            text = DES_dec_round(j, key_perm1, text);
            // cout << "Round " << j << " " << bin2hex(text) << "\n";
        }
        text = permute(text, inv_initial_prem, 64);
        // cout << "cipher after initial permutation: " << bin2hex(text) << "\n";
        result += bin2hex(text);
    }
    return result;
}

int main(void)
{
    string key = "527558F99B89BCB6";
    string text = "";

    ifstream myfile;
    myfile.open("key100k.txt");
    myfile >> text;

    cout << text << "\n";

    // cout << "Original text: " << text << "\n";

    key = hex2bin(key);
    text = hex2bin(text);

    string cipher, original_text;

    auto start = high_resolution_clock::now();

    cipher = encrypt(key, text);
    cout << "Encryption: " << cipher << "\n";

    cipher = hex2bin(cipher);

    original_text = decrypt(key, cipher);
    cout << "Decryption: " << original_text << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;
}