#include "hillCipher.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

int main(void)
{
    try {
        PolyGraphicCipher::Hill Cipher;

        // encryption
        Cipher.doEncrypt();
        Cipher.printEncryptedCode();

        // decryption
        Cipher.onlyDecrypt();
        Cipher.printDecryptedCode();
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
    std::flush(std::cout);
}
