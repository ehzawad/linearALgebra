#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

#include "inputValidate.hpp"
#include "linuxUtil.hpp"
#include "mathUtilities.hpp"
#include <climits>
#include <iomanip>
#include <stdexcept>
#include <string>

// core class of Hill Cipher logic
// other namespace is actually a helper class
class Hill {
private:
    // user input text
    std::string inputText;
    MathUtility::VV encryptedCodeString;
    MathUtility::VV decryptedCodeString;
    // this length determine the matrix size
    size_t splitLength;

public:
    // setter and getter of string
    void setText(void);
    // get inputText text
    std::string getText(void);
    // on the fly, it will encipher and decipher the text
    void splittingOnTheFly(MathUtility::VV&, std::string&, size_t tokens, size_t split, MathUtility::VV&, MathUtility::VV&, MathUtility::VV&);
    // just tokenize the whole string
    void tokenizer(std::string&);
    // will call the tokenizer method
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
void Hill::setText(void)
{
    // Instantiation of linux terminal process
    // this method will hide input for short time
    termios process = linuxUtil::setNotEchoingMode();
    // input the string from the user
    // which esseentially check REGEX pattern
    // null input will not allowd here
    this->inputText = ValidateInput::inputData("message", ".+");

    // remember you have gone to NOT ECHOING mode
    // so you have to revert back to previous state
    linuxUtil::goBack(process);
}

// get inputText text
std::string Hill::getText(void)
{
    return this->inputText;
}

// this will dynamically push chipherCode string =,
// which is esseentially a two dimensional vector
// the splliting part pushed from splittingOnTheFly() method
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

// the heart of the Hill Cipher Program
void Hill::splittingOnTheFly(MathUtility::VV& dimVariantMat, std::string& vec, size_t tokens, size_t split, MathUtility::VV& holder, MathUtility::VV& keyMatrix, MathUtility::VV& inverseKeyMatrix)
{
    // this type of declaration will initialize the the variable with value zero
    size_t counter{};
    for (size_t i = 0; i < tokens; i++) {
        // dynamically splittingOnTheFly the string
        // dynamically split the vector, copy upto to length split size
        std::copy_n(vec.begin(), split, std::back_inserter(dimVariantMat[i]));

        // change dimension of vector
        holder = MathUtility::Helper::dimensionVariantReturn(dimVariantMat[i], split);

        // doing multiple with keyMatrix
        MathUtility::VV enciphered = MathUtility::doMultiple(keyMatrix, holder);

        // after cipher
        std::cout << "EncryptedToken[" << std::setw(2) << ++counter << " ] -- ";
        MathUtility::Helper::dimensionVariantPrint(enciphered, split);

        // this will help us to store the whole string in vector
        encryptedCode(enciphered);

        // decipher the text
        MathUtility::VV decrypt = MathUtility::doMultiple(inverseKeyMatrix, enciphered);

        std::cout << "DecryptedToken[" << std::setw(2) << counter << " ] -- ";
        MathUtility::Helper::dimensionVariantPrint(decrypt, split);

        decryptedCode(decrypt);

        // dynamically decreease the vector by using C++ erasing Template
        // dynamically erase the string(std::vector) size
        vec.erase(vec.begin(), vec.begin() + split);
    }
}

void Hill::tokenizer(std::string& vec)
{
    // determine the token size
    size_t tokens{};
    // helper variable to size of split
    size_t spaceFactor{};

    if (vec.size() % 2 == 0) {
        tokens = vec.size() / 2;
        spaceFactor = vec.size();
    } else if ((vec.size() % 2 != 0) && MathUtility::isPrime(vec.size())) {
        vec.resize(vec.size() + 1);
        tokens = (vec.size() / 2);
        spaceFactor = vec.size();
    } else {
        tokens = vec.size() / 3;
        spaceFactor = vec.size();
    }

    std::cout << "TokenSize : " << tokens << std::endl;
    size_t split = (spaceFactor % 2 == 0) ? 2 : 3;
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

    // most important method of Hill Cipher Class
    splittingOnTheFly(twoD, vec, tokens, split, holder, keyMatrix, inverseKeyMatrix);
}

void Hill::statementToken()
{
    try {
        // this will promt input from the user
        setText();

        // copy user input string in vec variable
        std::string vec = this->inputText;
        // space is ignored now
        // lambda function
        vec.erase(std::remove_if(vec.begin(), vec.end(),
                      [](char x) { return std::isspace(x); }),
            vec.end());
        std::cout << getText();
        std::cout << std::endl;
        // caling tokenizer method
        tokenizer(vec);
        // three dots is heloful because, it will exception
        // whatever it is, if try block throw an exception
    } catch (...) {
        std::cout << "Something wrong there ! " << std::endl;
    }
}

#endif
