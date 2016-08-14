#ifndef _INDEX
#define _INDEX

#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>

#define NUM_LETTERS 26

namespace PseudoIndex {
// converting englist letters to corresponding number
// required for hill cipher or other cipher like ceaser cipher
// A - 1
// B - 1
// .... Z - 26
// also same for small letters
//
int engAlphabet(const char character)
{
    // JUST look at the ASCII value and
    // think about it
    if (std::isalpha(character) && std::isupper(character)) {
        return (character - 'A' + 1);
    } else if (std::isalpha(character) && std::islower(character)) {
        return (character - 'a' + 1 + NUM_LETTERS);
    } else if ((int)character >= 32 && (int)character <= 64) {
        return (character - ' ' + 1 + NUM_LETTERS + NUM_LETTERS);
    } else {
        return (character - '{' + 1 + NUM_LETTERS + NUM_LETTERS + 32);
    }
}

void printPseudoIndexedChar(int result, std::ostream& output = std::cout)
{
    // virtually I am taking all character from their ASCII list
    // that's why that is not actual index or shifting
    // As ASCII table is crappy, Implementation is crapy
    if (result >= 1 && result <= 26) {
        output << std::setw(1) << std::fixed << (char)(result + 'A' - 1);
    } else if (result >= 27 && result <= 52) {
        output << std::setw(1) << std::fixed << (char)(result + 70);
    } else if (result >= 53 && result <= 84) {
        output << std::setw(1) << std::fixed << (char)(result - 21);
    } else if (result >= 85 && result <= 88) {
        output << std::setw(1) << std::fixed << (char)(result + 38);
    }

    // this part for rotate back to charater of deCipher text's chracter
    if (result >= 89) {
        output << std::setw(1) << std::fixed << (char)((result % 88) + 32);
    }
    output << " ";
}

// namespace end
}

#endif
