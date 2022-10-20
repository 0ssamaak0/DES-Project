# DES Encryption / Decryption
# Program Structure

## 1. constans.cpp
contains all the permutation and expansion, required shift matrices

## 2. numsys.cpp
![numsys](https://github.com/0ssamaak0/DES-Project/blob/master/numsys.png)
contains function to convert between many systems as following

## 3.operations.cpp
[permute](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L5) takes the string, permutes it with the given permutation matrix in the specified size.

[shift_lift](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L15) takes the key, shifts it according to the number of round

[XOR](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L36) takes two HEX numbers and apply bitwise XOR operation

[Fesitel_func](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L69) apply the Feistel function to the text with the given key

[key_preparation](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L131) prepares the key in the beginning of each round (encryption or decryption)


[DES_enc_round](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L158) applies a full encryption round according to the given round number

[DES_dec_round](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/operations.cpp#L177) applies a full decryption round according to the given round number

## 4. main_threaded.cpp
The main file, in which we handle the I/O operations, and applying the full encryption / decryption

[enc_block](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/main_threaded.cpp#L16) applies encryption for a 64 bit block

[dec_block](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/main_threaded.cpp#L42) applies decryption for a 64 bit block

[encrypt](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/main_threaded.cpp#L138) applies encryption on the full_text

[decrypt](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/main_threaded.cpp#L159) applies decryption on the full_text

[hex_reader](https://github.com/0ssamaak0/DES-Project/blob/9456242a66f37f03913d824bfde76740f07c9390/main_threaded.cpp#L254) reads **file.hex** (it was stated previously that the program should read .hex files)

# Implementation Details
The first version of the program was single threaded
