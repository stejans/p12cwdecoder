#include "morse.h"

const MorseMap morseTable[] = {
    {'A', 0b101},
    {'B', 0b11000},
    {'C', 0b11010},
    {'D', 0b1100},
    {'E', 0b10},
    {'F', 0b10010},
    {'G', 0b1110},
    {'H', 0b10000},
    {'I', 0b100},
    {'J', 0b10111},
    {'K', 0b1101},
    {'L', 0b10100},
    {'M', 0b111},
    {'N', 0b110},
    {'O', 0b1111},
    {'P', 0b10110},
    {'Q', 0b11101},
    {'R', 0b1010},
    {'S', 0b1000},
    {'T', 0b11},
    {'U', 0b1001},
    {'V', 0b10001},
    {'W', 0b1011},
    {'X', 0b11001},
    {'Y', 0b11011},
    {'Z', 0b11100},
    {'0', 0b111111},
    {'1', 0b101111},
    {'2', 0b100111},
    {'3', 0b100011},
    {'4', 0b100001},
    {'5', 0b100000},
    {'6', 0b110000},
    {'7', 0b100111},
    {'8', 0b100011},
    {'9', 0b100001},
    {'.', 0b1010101},
    {',', 0b1110011},
    {':', 0b1111000},
    {';', 0b1101010},
    {'!', 0b1101011},
    {'"', 0b1010010},
    {'$', 0b10001001},
    {'/', 0b110010},
    {'=', 0b110001},
    {'-', 0b1100001},
    {'_', 0b1001101},
    {'+', 0b101010},
    {'\'', 0b1011110},
    {'@', 0b1011010},
    {'&', 0b101000},
    {'(', 0b110110},
    {')', 0b1101101},
    {'?', 0b1001100} // muss am Ende der Tabelle stehen!!!
};

const word morseTableSize = sizeof(morseTable)/sizeof(MorseMap);

char morse2char(byte m, bool replace) {
    for (int i=0; i<morseTableSize; i++) {
        if (morseTable[i].code==m) {
            return morseTable[i].letter;
        }
    }
    if (replace) {
        return morseTable[morseTableSize-1].letter;
    } else {
        return 0;
    }
}

const MorseMap& char2morse(char c) {
    for (int i=0; i<morseTableSize; i++) {
        if (morseTable[i].letter==c) {
            return morseTable[i];
        }
    }
    return morseTable[morseTableSize-1];
}
