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
        text = text.substr(32) + text.substr(0, 32);
        text = permute(text, inv_initial_prem, 64);
        result += bin2hex(text);
    }
    return result;
}

int main(void)
{
    string key = "5B0C1DA0F12AF1F2";
    string text = "C7526025FF6F8499D5100C2F189C81F754895C82AD723BCB3263F5B387EB68760941C406F256881E465A11F105A3447D994232050FDCAC205DDDA187953E98A533F205B974F565E3BF33727C735EE1F7ABCD4F991CC54A3F211B2A38F7A28FE169D3C77154596191E650EC3E8B71C2E235A9CF681D7149700BD36141A3F8D40BD4EEFB9C420854786BBE7C45820494E9054750FF76E23BB7DF4170B6E400A0387FCE7C639B4ED78456E947D2C7AB38764237DF707871DC5374E62739B8A509D3E07165073B3ADFE6E8D34650D3F1FD93EE43EC92E131FE0A6E332EEACDD35255018415A4FAB3899690B51217D699E61E5286826D99F16B8819519B2F4F6133F09F5A79883D5991F711F07ADACA9B35A01E16D9AA208749E1508E53AD961D04422865F84AE87B9CA8CD775937AC34BE04A6710CC98AC9447CDFA63B5C47C4DC82FC5B9A6E5D07DA7655B5A84AC665B0FFD68535F4D678527CFCA329C1BA108EE8E6AE08B1029F40AD0D22C573EE01B151CFEB616AC73592669CF042CAE1E332B8430EB73F6B75810D27C752AA6348CB93DA76C948C42AE388C7963889101E0D3074EB9D9FC3860D514C02DFD8BD46FFEE28B272B428EC73DBC5DEEA162C958EE090A917A333CF5FBECFFA01BCA001A471CC0E96DF184E6D5FA63E5AE03E935078BF7E340AEA37755FB085AA924A8EE81A93EEAF63";

    key = hex2bin(key);
    text = hex2bin(text);

    cout << encrypt(key, text) << "\n";
}