# DES Encryption / Decryption
# Program Structure

## 1. constans.cpp
contains all the permutation and expansion, required shift matrices

## 2. numsys.cpp
contains function to convert between many systems as following

## 3.operations.cpp
[permute] takes the string, permutes it with the given permutation matrix in the specified size.

[shift_lift] takes the key, shifts it according to the number of round

[XOR] takes two HEX numbers and apply bitwise XOR operation

[Fesitel_func] apply the Feistel function to the text with the given key

[key_preparation] prepares the key in the beginning of each round (encryption or decryption)


[DES_enc_round] applies a full encryption round according to the given round number

[DES_dec_round] applies a full decryption round according to the given round number

## 4. main.cpp
The main file, in which we handle the I/O operations, and applying the full encryption / decryption

[enc_block] applies encryption for a 64 bit block

[dec_block] applies decryption for a 64 bit block

[encrypt] applies encryption on the full_text

[decrypt] applies decryption on the full_text

[hex_reader] reads **file.hex** (it was stated previously that the program should read .hex files)
