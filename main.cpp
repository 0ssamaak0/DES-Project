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

string enc_block(string key, string text)
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
    for (int i = 0; i < full_text.size() / 64; i++)
    {
        string text = full_text.substr(64 * i, 64);
        // cout << "text for " << i << " is " << bin2hex(text) << "\n";
        string block_res = enc_block(key, text);
        result += block_res;
    }
    return result;
}

string dec_block(string key, string text)
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
    for (int i = 0; i < full_text.size() / 64; i++)
    {
        string text = full_text.substr(64 * i, 64);
        // cout << "text for " << i << " is " << bin2hex(text) << "\n";
        string block_res = dec_block(key, text);
        result += block_res;
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
    string key = "527558F99B89BCB6";
    string text = "8C9CB199D355CF1BA26EB628A8091E0537F573F8E04284D71F9045FFA47C40E95B386C61B74EF9CD068FE3947260E602946B3D0DC76AF965AC31D917084AE1B5028369679A37D56862C09FB0D823B9F6A3A3BCE25F44C9E1A6E010F3FE7B80E2CA0987E4B8EB5A479C6910111AE8B9F9F825F85BAFDE009C6805469DC5821114B493FA76814798AE678C2F2ACB6CDE46870639FABBFDBBDE629237FCCAB4EFF016D2C6DA5DA5FC7DBF85682B0666E028264B5DF8C88646C0B55CB66EDFAB71725E299B36A302DA8C46159E23C6BBF3889431351A8B86EEE0FBA03626EC3E38F668AEB868652899421F40E3005193D99F3BB703626F16A941A4263F44C491A921F4FAA255A1B4270D703F859F9E8C17B3FC33B3862A02A7AB1299BA3B456542380AD20E991C8B941B18FCCE72ECA23991A77339D100B78AAE42BC441DCE55DC072F7D2698BD60D269734C70E2DCBD001F7D2B01AD18AE4D5B807A6AC235CD44F4DA560C9D4CFFA508DBEC45A62A12AA6CBF9238AF4409B624118FCAA1A359048D12C7228AB70FAA6454E6FCB777F3352BE692CADDAFB17750A2467DE7A1E764AABB7D4EFABF482C69599C7AEF9D54043BC1280D17FB6F566C7E3A6CD4117234E56201E05D6D9010D04DB9DF42DCA292496AB83F4D9FB0D0626C8CD506FBAEC30E17F18FD9D0A227B8CEC00B46D45466E2F2ADBFC5";
    int digits = 0;
    // string filename = "sample.hex";
    // text = hex_reader(filename);

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
    cout << "Time in ms: " << duration.count() << endl;
}