using namespace std;

string function_outputs[16];

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
    return s;
}

// TODO bitwise operation
string XOR(string x, string y)
{
    long long int_x = binary2decimal(x);
    long long int_y = binary2decimal(y);

    long long int_xor = int_x ^ int_y;
    // cout << "x: " << x << "\ny: " << y << "\n";
    // cout << "intx: " << int_x << "\ninty: " << int_y << "\n";

    string strxor = decimal2binary(int_xor);
    // cout << "intxor: " << int_xor << "\n";
    // cout << "strxor: " << strxor << "\n";

    while (strxor.size() < x.size())
    {
        strxor = "0" + strxor;
    }
    return strxor;

    // string result = "";
    // for (int i = 0; i < x.size(); i++)
    // {
    //     if (x[i] != y[i])
    //     {
    //         result += "1";
    //     }
    //     else
    //     {
    //         result += "0";
    //     }
    // }
    // return result;
}
string Fesitel_func(string s, string key)
{
    s = permute(s, expansion, 48);

    // cout << bin2hex(text_right) << "\n";

    // XOR
    string XOR1 = XOR(key, s);
    // cout << "XOR1: " << bin2hex(XOR1) << "\n";

    // SBOX
    string bin_value = "";
    for (int i = 0; i < 8; i++)
    {
        // Row number
        int row = 0;
        if (XOR1[i * 6] != '0')
        {
            row += 2;
        }
        if (XOR1[i * 6 + 5] != '0')
        {
            row += 1;
        }

        // Col number
        int col = 0;
        if (XOR1[i * 6 + 1] != '0')
        {
            col += 8;
        }
        if (XOR1[i * 6 + 2] != '0')
        {
            col += 4;
        }
        if (XOR1[i * 6 + 3] != '0')
        {
            col += 2;
        }
        if (XOR1[i * 6 + 4] != '0')
        {
            col += 1;
        }
        int value = sbox[i][row][col];
        // cout << "val " << value << "\n";
        string dec2bin = decimal2binary(value);
        while (dec2bin.size() < 4)
        {
            dec2bin = "0" + dec2bin;
        }
        bin_value += dec2bin;
        // cout << "bin_value: " << bin2hex(bin_value) << "\n";
    }

    // cout << "SBOX Otput " << bin2hex(bin_value) << "\n";

    // Permutation after SBOX
    string permutation_after_sbox = permute(bin_value, perm, 32);

    return permutation_after_sbox;
}

string key_preparation(string key, int round_num)
{
    // Preparing the key
    string key_left = key.substr(0, 28);
    string key_right = key.substr(28);

    // cout << key_left.size() << "\n";
    // cout << key_right.size() << "\n";
    int shift = 0;
    for (int i = 0; i <= round_num; i++)
    {
        shift += shift_amt[i];
    }

    key_left = shift_left(key_left, shift);
    key_right = shift_left(key_right, shift);

    key = key_left;
    // cout << "key1: " << key << "\n";
    key += key_right;
    // cout << "key2: " << key << "\n";

    // Permutation choice 2
    string key_perm_2 = permute(key, perm_2, 48);
    return key_perm_2;
}

string DES_enc_round(int round_num, string key, string text)
{
    key = key_preparation(key, round_num);
    // cout << "Key of Round " << round_num << " is " << bin2hex(key) << "\n";

    // cout << key_perm_2 << "\n";

    // Preparing the text
    string text_left = text.substr(0, 32);
    string text_right = text.substr(32);

    string result_left = text_right;
    string result_right = XOR(text_left, Fesitel_func(text_right, key));

    string result_text = result_left;
    result_text += result_right;

    return result_text;
}
string DES_dec_round(int round_num, string key, string cipher)
{
    key = key_preparation(key, round_num);

    // Preparing the cipher
    string cipher_left = cipher.substr(0, 32);
    string cipher_right = cipher.substr(32);

    string result_right = cipher_left;
    string result_left = XOR(cipher_right, Fesitel_func(cipher_left, key));

    string result_cipher = result_left;
    result_cipher += result_right;

    return result_cipher;
}