#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

#include "constants.cpp"
#include "numsys.cpp"
#include "operations.cpp"

using namespace std;
using namespace std::chrono;

string block_res[16];

string enc_block(string key, string text, int block_num)
{
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
    string result = bin2hex(text);
    block_res[block_num] = bin2hex(text);
    return result;
}

string encrypt(string key, string full_text)
{
    string result = "";
    // padding
    while (full_text.size() % 64 != 0)
    {
        full_text += "0";
    }
    long long num_blocks = full_text.size() / 64;
    // if (1) // to test the performance vs single threaded
    if (num_blocks < 16)
    {
        // cout << "numblocks < 16\n";
        for (int i = 0; i < full_text.size() / 64; i++)
        {
            string text = full_text.substr(64 * i, 64);
            // cout << "text for " << i << " is " << bin2hex(text) << "\n";
            string block_res = enc_block(key, text, 0);
            result += block_res;
        }
    }
    else
    {
        // cout << "numblocks > 16\n";
        long long counter = 0;
        while (num_blocks - counter >= 16)
        {
            // cout << "new loop at " << counter << "\n";
            thread th1_a(enc_block, key, full_text.substr(64 * counter, 64), 0);
            counter++;
            thread th2_a(enc_block, key, full_text.substr(64 * counter, 64), 1);
            counter++;
            thread th3_a(enc_block, key, full_text.substr(64 * counter, 64), 2);
            counter++;
            thread th4_a(enc_block, key, full_text.substr(64 * counter, 64), 3);
            counter++;
            thread th5_a(enc_block, key, full_text.substr(64 * counter, 64), 4);
            counter++;
            thread th6_a(enc_block, key, full_text.substr(64 * counter, 64), 5);
            counter++;
            thread th7_a(enc_block, key, full_text.substr(64 * counter, 64), 6);
            counter++;
            thread th8_a(enc_block, key, full_text.substr(64 * counter, 64), 7);
            counter++;
            thread th1_b(enc_block, key, full_text.substr(64 * counter, 64), 8);
            counter++;
            thread th2_b(enc_block, key, full_text.substr(64 * counter, 64), 9);
            counter++;
            thread th3_b(enc_block, key, full_text.substr(64 * counter, 64), 10);
            counter++;
            thread th4_b(enc_block, key, full_text.substr(64 * counter, 64), 11);
            counter++;
            thread th5_b(enc_block, key, full_text.substr(64 * counter, 64), 12);
            counter++;
            thread th6_b(enc_block, key, full_text.substr(64 * counter, 64), 13);
            counter++;
            thread th7_b(enc_block, key, full_text.substr(64 * counter, 64), 14);
            counter++;
            thread th8_b(enc_block, key, full_text.substr(64 * counter, 64), 15);
            counter++;

            th1_a.join();
            th2_a.join();
            th3_a.join();
            th4_a.join();
            th5_a.join();
            th6_a.join();
            th7_a.join();
            th8_a.join();
            th1_b.join();
            th2_b.join();
            th3_b.join();
            th4_b.join();
            th5_b.join();
            th6_b.join();
            th7_b.join();
            th8_b.join();

            for (int i = 0; i < 16; i++)
            {
                result += block_res[i];
                // cout << block_res[i] << " blockres!\n";
            }
        }
        // cout << num_blocks - counter << "\n";
        for (int i = 0; i < num_blocks - counter; i++)
        {
            // cout << "left is less than 16\n";
            string rem_block_res = enc_block(key, full_text.substr((i + counter) * 64, 64), 0);
            // cout << "Fulltext in counter " << i + counter << " : " << bin2hex(full_text.substr(64 * i + counter, 64)) << "\n";
            result += rem_block_res;
        }
    }
    return result;
}

string dec_block(string key, string text, int block_num)
{
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
    string result = bin2hex(text);
    block_res[block_num] = bin2hex(text);
    return result;
}

string decrypt(string key, string full_text)
{
    string result = "";
    // padding
    while (full_text.size() % 64 != 0)
    {
        full_text += "0";
    }
    long long num_blocks = full_text.size() / 64;
    // if (1) // to test the performance vs single threaded
    if (num_blocks < 16)
    {
        // cout << "numblocks < 16\n";
        for (int i = 0; i < full_text.size() / 64; i++)
        {
            string text = full_text.substr(64 * i, 64);
            // cout << "text for " << i << " is " << bin2hex(text) << "\n";
            string block_res = dec_block(key, text, 0);
            result += block_res;
        }
    }
    else
    {
        // cout << "numblocks > 16\n";
        long long counter = 0;
        while (num_blocks - counter >= 16)
        {
            // cout << "new loop at " << counter << "\n";
            thread th1_a(dec_block, key, full_text.substr(64 * counter, 64), 0);
            counter++;
            thread th2_a(dec_block, key, full_text.substr(64 * counter, 64), 1);
            counter++;
            thread th3_a(dec_block, key, full_text.substr(64 * counter, 64), 2);
            counter++;
            thread th4_a(dec_block, key, full_text.substr(64 * counter, 64), 3);
            counter++;
            thread th5_a(dec_block, key, full_text.substr(64 * counter, 64), 4);
            counter++;
            thread th6_a(dec_block, key, full_text.substr(64 * counter, 64), 5);
            counter++;
            thread th7_a(dec_block, key, full_text.substr(64 * counter, 64), 6);
            counter++;
            thread th8_a(dec_block, key, full_text.substr(64 * counter, 64), 7);
            counter++;
            thread th1_b(dec_block, key, full_text.substr(64 * counter, 64), 8);
            counter++;
            thread th2_b(dec_block, key, full_text.substr(64 * counter, 64), 9);
            counter++;
            thread th3_b(dec_block, key, full_text.substr(64 * counter, 64), 10);
            counter++;
            thread th4_b(dec_block, key, full_text.substr(64 * counter, 64), 11);
            counter++;
            thread th5_b(dec_block, key, full_text.substr(64 * counter, 64), 12);
            counter++;
            thread th6_b(dec_block, key, full_text.substr(64 * counter, 64), 13);
            counter++;
            thread th7_b(dec_block, key, full_text.substr(64 * counter, 64), 14);
            counter++;
            thread th8_b(dec_block, key, full_text.substr(64 * counter, 64), 15);
            counter++;

            th1_a.join();
            th2_a.join();
            th3_a.join();
            th4_a.join();
            th5_a.join();
            th6_a.join();
            th7_a.join();
            th8_a.join();
            th1_b.join();
            th2_b.join();
            th3_b.join();
            th4_b.join();
            th5_b.join();
            th6_b.join();
            th7_b.join();
            th8_b.join();

            for (int i = 0; i < 16; i++)
            {
                result += block_res[i];
                // cout << block_res[i] << " blockres!\n";
            }
        }
        // cout << num_blocks - counter << "\n";
        for (int i = 0; i < num_blocks - counter; i++)
        {
            // cout << "left is less than 16\n";
            string rem_block_res = dec_block(key, full_text.substr((i + counter) * 64, 64), 0);
            // cout << "Fulltext in counter " << i + counter << " : " << bin2hex(full_text.substr(64 * i + counter, 64)) << "\n";
            result += rem_block_res;
        }
    }
    return result;
}
string hex_reader(string filename)
{
    string line = "";
    string text = "";
    int digits;
    ifstream MyReadFile(filename);
    while (getline(MyReadFile, line))
    {
        // Output the text from the file
        // cout << text.substr(1,2);
        digits = hextodecimal(line.substr(1, 2));
        text += line.substr(9, digits * 2);
    }
    return text;
}

int main(void)
{
    string key = "3644607B8DCE037F";
    string text = "";
    int digits = 0;

    // reading hex_file
    // string filename = "long_sample.hex";
    // text = hex_reader(filename);

    // reading txt_file
    ifstream file;
    file.open("key.txt");
    file >> text;

    // reading
    key = hex2bin(key);
    text = hex2bin(text);

    // Writing cipher output to the file
    ofstream out("output.txt");

    string cipher, original_text;

    auto start = high_resolution_clock::now();

    cipher = encrypt(key, text);
    cout << "Encryption: " << cipher << "\n";
    out << "Encryption: " << cipher << "\n";

    cipher = hex2bin(cipher);

    original_text = decrypt(key, cipher);
    cout << "Decryption: " << original_text << "\n";
    out << "Decryption: " << original_text << "\n";

    cout << "text size " << bin2hex(text).size() << "\n";
    cout << "cipher size " << bin2hex(cipher).size() << "\n";
    cout << "decrypted size " << original_text.size() << "\n";

    out << "text size " << bin2hex(text).size() << "\n";
    out << "cipher size " << bin2hex(cipher).size() << "\n";
    out << "decrypted size " << original_text.size() << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time in ms: " << duration.count() << endl;
}