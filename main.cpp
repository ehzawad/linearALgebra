#include "hillCipher.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>

int main(void)
{
    try {
        PolyGraphicCipher::Hill Cipher;

        // encryption
        Cipher.doEncrypt();
        Cipher.printEncryptedCode();
        // C++11 threading
        // pause before continuing
        // http://en.cppreference.com/w/cpp/thread/sleep_for
        // The process thread will hold for 1 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // decryption
        Cipher.onlyDecrypt();
        Cipher.printDecryptedCode();
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
    std::flush(std::cout);
}
