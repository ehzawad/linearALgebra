#ifndef _INDEX
#define _INDEX

#include <cctype>

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
    if (std::isalpha(character) && std::isupper(character)) {
        return (character - 'A' + 1);
    } else if (std::isalpha(character) && std::islower(character)) {
        return (character - 'a' + 1);
    } else {
        return 0;
    }
}
}

#endif
