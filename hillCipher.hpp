#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

#include "inputValidate.hpp"
#include "linuxUtil.hpp"
#include "mathUtilities.hpp"
#include <climits>
#include <iomanip>
#include <stdexcept>
#include <string>

#define ONECOLUMN 1

class Hill {
private:
    std::string encryptText;
    MathUtility::VV encryptedCodeString;
    MathUtility::VV decryptedCodeString;
    size_t splitLength;

public:
    // setter and getter of string
    void setEncryptText(void);
    // get encryptText text
    std::string getEncryptText(void);
    void splittingOnTheFly(MathUtility::VV&, std::string&, size_t tokens, size_t split, MathUtility::VV&, MathUtility::VV&, MathUtility::VV&);
    void tokenizer(std::string&);
    void statementToken(void);

    // this is directly store encrypted code
    void encryptedCode(MathUtility::VV&);
    void printEncryptedCode(void);
    // this is directly store decrypted code
    void decryptedCode(MathUtility::VV&);
    void printDecryptedCode(void);
};

void Hill::printEncryptedCode()
{
    std::cout << "encrypted String : " << std::endl;
    MathUtility::Helper::printMatrixVariant(this->encryptedCodeString);
    std::cout << std::endl;
}

void Hill::printDecryptedCode()
{
    std::cout << "decrypted String : " << std::endl;
    MathUtility::Helper::printMatrixVariant(this->decryptedCodeString);
    std::cout << std::endl;
}

// Implementation of hill class
void Hill::setEncryptText(void)
{
    termios process = linuxUtil::setNotEchoingMode();
    this->encryptText = ValidateInput::inputData("message", ".+");
    linuxUtil::goBack(process);
}

// get encryptText text
std::string Hill::getEncryptText(void)
{
    return this->encryptText;
}

void Hill::encryptedCode(MathUtility::VV& cipherCode)
{
    for (auto& hillCipheredCode : cipherCode) {
        encryptedCodeString.push_back(hillCipheredCode);
    }
}

void Hill::decryptedCode(MathUtility::VV& deCipherCode)
{
    for (auto& hillCipheredCode : deCipherCode) {
        decryptedCodeString.push_back(hillCipheredCode);
    }
}

void Hill::splittingOnTheFly(MathUtility::VV& dimVariantMat, std::string& vec, size_t tokens, size_t split, MathUtility::VV& holder, MathUtility::VV& keyMatrix, MathUtility::VV& inverseKeyMatrix)
{
    size_t counter{};
    for (size_t i = 0; i < tokens; i++) {
        // dynamically splittingOnTheFly the string
        std::copy_n(vec.begin(), split, std::back_inserter(dimVariantMat[i]));
        // change dimension of vector
        holder = MathUtility::Helper::dimensionVariantReturn(dimVariantMat[i], split);
        // doing multiple with keyMatrix
        MathUtility::VV heal = MathUtility::doMultiple(keyMatrix, holder);

        // after cipher
        std::cout << "EncryptedToken[" << std::setw(2) << ++counter << " ] -- ";
        MathUtility::Helper::dimensionVariantPrint(heal, split);

        // this will help us to the whole string in vector
        encryptedCode(heal);

        MathUtility::VV decrypt = MathUtility::doMultiple(inverseKeyMatrix, heal);

        std::cout << "DecryptedToken[" << std::setw(2) << counter << " ] -- ";
        MathUtility::Helper::dimensionVariantPrint(decrypt, split);

        decryptedCode(decrypt);

        // dynamically decreease the vector by using C++ erasing Template
        vec.erase(vec.begin(), vec.begin() + split);
    }
}

void Hill::tokenizer(std::string& vec)
{
    size_t tokens{};
    size_t spaceFact{};

    if (vec.size() % 2 == 0) {
        tokens = vec.size() / 2;
        spaceFact = vec.size();
    } else if ((vec.size() % 2 != 0) && MathUtility::isPrime(vec.size())) {
        vec.resize(vec.size() + 1);
        tokens = (vec.size() / 2);
        spaceFact = vec.size();
    } else {
        tokens = vec.size() / 3;
        spaceFact = vec.size();
    }

    std::cout << "TOkensize : " << tokens << std::endl;
    size_t split = (spaceFact % 2 == 0) ? 2 : 3;
    this->splitLength = split;

    MathUtility::VV twoD(tokens);
    MathUtility::VV holder(split, MathUtility::V(split, 0));
    MathUtility::VV keyMatrix = MathUtility::makeMatrix(split, split);

    std::cout << "Enter your Matrix(" << split << "X" << split << ")"
              << ", which will be used for Crypto -->";
    std::cout << std::endl;
    MathUtility::readMatrix(keyMatrix, std::cin);
    std::cout << std::endl;

    MathUtility::VV inverseKeyMatrix = MathUtility::findInverseMat(keyMatrix);
    std::cout << "Inverse of KeyMatrix : " << std::endl;
    MathUtility::printMatrix(inverseKeyMatrix);
    std::cout << std::endl;

    splittingOnTheFly(twoD, vec, tokens, split, holder, keyMatrix, inverseKeyMatrix);
}

void Hill::statementToken()
{
    try {
        setEncryptText();

        std::string vec = this->encryptText;
        // space is ignored now
        vec.erase(std::remove_if(vec.begin(),
                      vec.end(),
                      [](char x) { return std::isspace(x); }),
            vec.end());
        std::cout << getEncryptText();
        std::cout << std::endl;
        tokenizer(vec);
    } catch (...) {
        std::cout << "Something wrong there ! " << std::endl;
    }
}

#endif
