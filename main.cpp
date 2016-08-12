#include "hillCipher.hpp"
#include "mathUtilities.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

int main(void)
{
    try {
        Hill Cipher;

        Cipher.statementToken();
        std::cout << std::endl;
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
}
