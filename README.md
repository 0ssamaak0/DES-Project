# DES Encryption / Decryption

# Compiling the program
the new version of our program is Multi-Threaded, for compilation use:

``` bash
g++ -pthread -o main_threaded main_threaded.cpp
```

note: compilation without `pthread` option will result in undefined reference to `pthread_create' error.

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
## Single-Threaded Version
The first version of the program was single threaded, such an implementation bottlenecked single thread in a long sequential functions.

![single_threaded](https://github.com/0ssamaak0/DES-Project/blob/master/single_threaded.png)

## Multi-Threaded Version
In order to push the performance further and increase the utilization, we used 16 threads to perfrom all the operations just after dividing the text into more than 16 threads, from permutations, conversions and the whole ecnryption / decryption process.

The effect of the implementation was a dramatic decrease in required time, specially for CPUs with more cores.

![multi_threaded](https://github.com/0ssamaak0/DES-Project/blob/master/multi_threaded.png)

We made a comparison between both versions

![running_time](https://github.com/0ssamaak0/DES-Project/blob/master/running_time.png)
