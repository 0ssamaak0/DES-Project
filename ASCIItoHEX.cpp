#include <iostream>
 
using namespace std;
 
// function to convert decimal to hexadecimal
string decToHexa(int n)
{
    // char array to store hexadecimal number
    char hexaDeciNum[100];
 
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;
 
        // storing remainder in temp variable.
        temp = n % 16;
 
        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
 
    string ans = "";
 
    // printing hexadecimal number array in reverse order
    for (int j = i - 1; j >= 0; j--)
        ans += hexaDeciNum[j];
 
    return ans;
}

// Function to convert ASCII to HEX
string ASCIItoHEX(string ascii)
{
    // Initialize final String
    string hex = "";
 
    // Make a loop to iterate through every character of ascii string
    for (int i = 0; i < ascii.length(); i++) {
        // Take a char from position i of string
        char ch = ascii[i];
 
        // Cast char to integer and find its ascii value
        int tmp = (int)ch;
 
        // Change this ascii value integer to hexadecimal value
        string part = decToHexa(tmp);
 
        // Add this hexadecimal value to final string.
        hex += part;
    }
 
    // Return the final string hex
    return hex;
}
