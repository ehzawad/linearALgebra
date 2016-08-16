#include "hillCipher.hpp"
#include "mathUtilities.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

int main(void)
{
    try {
        PolyGraphichCipher::Hill Cipher;

        Cipher.statementToken();
        std::cout << std::endl;

        Cipher.printEncryptedCode();
        Cipher.printDecryptedCode();
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
    std::flush(std::cout);
}
