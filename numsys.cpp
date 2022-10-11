#include <iostream>
#include <string>
using namespace std;
string hex2bin(string s)
{
    string bin = "";
    for (int i = 0; i < s.size(); i++)
    {
        switch (s[i])
        {
        case '0':
            bin += "0000";
            break;
        case '1':
            bin += "0001";
            break;
        case '2':
            bin += "0010";
            break;
        case '3':
            bin += "0011";
            break;
        case '4':
            bin += "0100";
            break;
        case '5':
            bin += "0101";
            break;
        case '6':
            bin += "0110";
            break;
        case '7':
            bin += "0111";
            break;
        case '8':
            bin += "1000";
            break;
        case '9':
            bin += "1001";
            break;
        case 'A':
            bin += "1010";
            break;
        case 'B':
            bin += "1011";
            break;
        case 'C':
            bin += "1100";
            break;
        case 'D':
            bin += "1101";
            break;
        case 'E':
            bin += "1110";
            break;
        case 'F':
            bin += "1111";
            break;
        }
    }
    return bin;
}

string bin2hex(string s)
{
    string hex = "";
    for (int i = 0; i < s.size(); i += 4)
    {
        string val = "";

        val += s[i];
        val += s[i + 1];
        val += s[i + 2];
        val += s[i + 3];

        if (val == "0000")
        {
            hex += '0';
        }
        else if (val == "0001")
        {
            hex += '1';
        }
        else if (val == "0010")
        {
            hex += '2';
        }
        else if (val == "0011")
        {
            hex += '3';
        }
        else if (val == "0100")
        {
            hex += '4';
        }
        else if (val == "0101")
        {
            hex += '5';
        }
        else if (val == "0110")
        {
            hex += '6';
        }
        else if (val == "0111")
        {
            hex += '7';
        }
        else if (val == "1000")
        {
            hex += '8';
        }
        else if (val == "1001")
        {
            hex += '9';
        }
        else if (val == "1010")
        {
            hex += 'A';
        }
        else if (val == "1011")
        {
            hex += 'B';
        }
        else if (val == "1100")
        {
            hex += 'C';
        }
        else if (val == "1101")
        {
            hex += 'D';
        }
        else if (val == "1110")
        {
            hex += 'E';
        }
        else if (val == "1111")
        {
            hex += 'F';
        }
    }
    return hex;
}

string decimal2binary(long long decimal)
{
    string bin = "";
    while (decimal > 0)
    {
        bin = (char)(decimal % 2 + '0') + bin;
        decimal /= 2;
    }
    return bin;
}

long long binary2decimal(string s)
{
    long long dec = 0;
    long long weight = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        dec += (long long)(s[i] - '0') * weight;
        weight *= 2;
    }
    return dec;
}

// For testing numsys functions only
// int main(void)
// {
//     //     string s = "0123456789ABCDEF";
//     //     string bin = hex2bin(s);

//     //     cout << bin << "\n";

//     //     string hex = bin2hex(bin);
//     //     cout << hex << "\n";

//     //     cout << decimal2binary(5) << "\n";
//     //     cout << decimal2binary(4) << "\n";
//     //     cout << decimal2binary(10) << "\n";
//     //     cout << decimal2binary(16) << "\n";

//     cout << binary2decimal("0101") << "\n";
//     cout << binary2decimal("1") << "\n";
//     cout << binary2decimal("0") << "\n";
//     cout << binary2decimal("000000") << "\n";
//     cout << binary2decimal("1100111010011100111") << "\n";
//     cout << binary2decimal("000010110000001001100111100110110100100110100101") << "\n";
// }