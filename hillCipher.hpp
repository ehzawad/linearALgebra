#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

#include "inputValidate.hpp"
#include "linuxUtil.hpp"
#include "mathUtilities.hpp"
#include <climits>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <tuple>

namespace PolyGraphicCipher {
// core class of Hill Cipher logic
// other namespace is actually a helper class
class Hill {
private:
    // user input text
    std::string inputText;
    // store encrypted code string
    MathUtility::VV encryptedCodeString;
    // store decrypted code string
    MathUtility::VV decryptedCodeString;

    // keyMatrix and it's inverseKeyMatrix too !
    MathUtility::VV keyMatrix;
    MathUtility::VV inverseKeyMatrix;
    // this length determine the matrix size
    size_t splitLength{};
    // this store the tokenSize
    size_t tokens{};
public:
    // setter and getter of string
    void setText(void);

    MathUtility::VV setMatKEY(void);
    MathUtility::VV getMatKEYInverse(MathUtility::VV& keyMat);

    // get inputText text
    std::string getText(void);

    void tokenSizeCalc(std::string& theString);

    std::tuple<MathUtility::VV, MathUtility::VV> keyMatrixAndItsInverseTuple(void);
    std::tuple<MathUtility::VV, MathUtility::VV> encipherDecipher(MathUtility::VV&, size_t, MathUtility::VV&, MathUtility::VV&);
    // on the fly, it will encipher and decipher the text
    void splittingOnTheFly(std::string&, MathUtility::VV&, MathUtility::VV&);
    // just tokenize the whole string
    void tokenizer(std::string&);
    // will call the tokenizer method
    void statementToken(void);

    // this is directly store encrypted code
    void encryptedCodeStorage(MathUtility::VV&);
    void printEncryptedCode(void);
    // this is directly store decrypted code
    void decryptedCodeStorage(MathUtility::VV&);
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
    std::cout << "Don't paranoid, At First Glance, It is Cryptical when you will type text\n"
              << "It is in hidden mode (NOT ECHOING anything as you type)" << std::endl;
    // Instantiation of linux terminal process
    // this method will hide input for short time
    linuxUtil::setNotEchoingMode();
    // input the string from the user
    // which esseentially check REGEX pattern
    // null input will not allowd here
    this->inputText = ValidateInput::inputData("message", ".+");

    // remember you have gone to NOT ECHOING mode
    // so you have to revert back to previous state
    linuxUtil::setEchoingMode();
}

// get inputText text
std::string Hill::getText(void)
{
    return this->inputText;
}

// this will dynamically push chipherCode string =,
// which is esseentially a two dimensional vector
// the splliting part pushed from splittingOnTheFly() method
void Hill::encryptedCodeStorage(MathUtility::VV& cipherCode)
{
    for (auto& hillCipheredCode : cipherCode) {
        this->encryptedCodeString.push_back(hillCipheredCode);
    }
}

void Hill::decryptedCodeStorage(MathUtility::VV& deCipherCode)
{
    for (auto& hillCipheredCode : deCipherCode) {
        this->decryptedCodeString.push_back(hillCipheredCode);
    }
}

std::tuple<MathUtility::VV, MathUtility::VV> Hill::encipherDecipher(MathUtility::VV& holder, size_t counter, MathUtility::VV& keyMatrix, MathUtility::VV& inverseKeyMatrix)
{
    // doing multiple with keyMatrix
    MathUtility::VV enciphered = MathUtility::doMultiple(keyMatrix, holder);

    // after cipher
    std::cout << "EncryptedToken[" << std::setw(2) << counter << " ] -- ";
    MathUtility::Helper::dimensionVariantPrint(enciphered, this->splitLength);

    // decipher the text
    MathUtility::VV deciphered = MathUtility::doMultiple(inverseKeyMatrix, enciphered);

    std::cout << "DecryptedToken[" << std::setw(2) << counter << " ] -- ";
    MathUtility::Helper::dimensionVariantPrint(deciphered, this->splitLength);

    return std::make_tuple(enciphered, deciphered);
}

// the heart of the Hill Cipher Program
void Hill::splittingOnTheFly(std::string& vec, MathUtility::VV& keyMatrix, MathUtility::VV& inverseKeyMatrix)
{
    // make room for holder Matrix and initialize it to zero
    // this type of declaration will initialize the the variable with value zero
    MathUtility::VV holder(this->splitLength, MathUtility::V(this->splitLength, 0));
    MathUtility::VV dimVariantMat(tokens);
    size_t counter{};
    for (size_t i = 0; i < this->tokens; i++) {
        counter++;
        // dynamically splittingOnTheFly the string
        // dynamically split the vector, copy upto to length split size
        std::copy_n(vec.begin(), this->splitLength, std::back_inserter(dimVariantMat[i]));

        // change dimension of vector
        holder = MathUtility::Helper::dimensionVariantReturn(dimVariantMat[i], this->splitLength);

        MathUtility::VV encipheredToken;
        MathUtility::VV decipheredToken;
        // tied with tuples
        std::tie(encipheredToken, decipheredToken) = encipherDecipher(holder, counter, keyMatrix, inverseKeyMatrix);

        encryptedCodeStorage(encipheredToken);
        decryptedCodeStorage(decipheredToken);

        // dynamically decrease the vector by using C++ erase of Vector Template
        // dynamically erase the string(std::vector) size
        vec.erase(vec.begin(), vec.begin() + this->splitLength);
    }
}

void Hill::tokenSizeCalc(std::string& theString)
{
    // determine the token size
    size_t numOfTokens{};
    // helper variable to size of split
    size_t spaceFactor{};

    if (theString.size() % 2 == 0) {
        numOfTokens = theString.size() / 2;
        spaceFactor = theString.size();
    } else if ((theString.size() % 2 != 0) && MathUtility::isPrime(theString.size())) {
        theString.resize(theString.size() + 1);
        numOfTokens = (theString.size() / 2);
        spaceFactor = theString.size();
    } else {
        numOfTokens = theString.size() / 3;
        spaceFactor = theString.size();
    }

    this->tokens = numOfTokens;
    std::cout << "TokenSize : " << this->tokens << std::endl;
    size_t split = (spaceFactor % 2 == 0) ? 2 : 3;
    this->splitLength = split;
}

MathUtility::VV Hill::setMatKEY(void)
{
    MathUtility::VV keyMatrix = MathUtility::makeMatrix(this->splitLength, this->splitLength);

    std::cout << "Enter your Matrix(" << splitLength << "X" << splitLength << ")"
              << ", which will be used for Crypto -->";
    std::cout << std::endl;
    MathUtility::readMatrix(keyMatrix, std::cin);
    std::cout << std::endl;

    return keyMatrix;
}

MathUtility::VV Hill::getMatKEYInverse(MathUtility::VV& keyMat)
{
    MathUtility::VV inverseKeyMatrix = MathUtility::findInverseMat(keyMat);
    std::cout << "Inverse of KeyMatrix : " << std::endl;
    if (inverseKeyMatrix.empty()) {
        return {};
    } else {
        MathUtility::printMatrix(inverseKeyMatrix);
        std::cout << std::endl;
        return inverseKeyMatrix;
    }
}

std::tuple<MathUtility::VV, MathUtility::VV> Hill::keyMatrixAndItsInverseTuple(void)
{
    this->keyMatrix = setMatKEY();
    this->inverseKeyMatrix = getMatKEYInverse(this->keyMatrix);

    // null vector must be checked
    if (inverseKeyMatrix.empty()) {
        return {};
    } else {
        return std::make_tuple(keyMatrix, inverseKeyMatrix);
    }
}

void Hill::tokenizer(std::string& vec)
{
    tokenSizeCalc(vec);

    MathUtility::VV keyMat;
    MathUtility::VV inverseKeyMat;

    std::tie(keyMat, inverseKeyMat) = keyMatrixAndItsInverseTuple();

    // most important method of Hill Cipher Class
    if (!inverseKeyMat.empty()) {
        splittingOnTheFly(vec, keyMat, inverseKeyMat);
    } else {
        return;
    }
}

void Hill::statementToken()
{
    try {
        // this will promt input from the user
        setText();
        // copy user input string in vec variable
        std::string vec = this->inputText;
        if (vec.size() >= 2) {
            // space is ignored now
            // lambda function
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                          [=](char x) { return std::iscntrl(x); }),
                vec.end());
            std::cout << getText();
            std::cout << std::endl;
            // caling tokenizer method
            tokenizer(vec);
            // three dots is heloful because, it will exception
            // whatever it is, if try block throw an exception
        } else {
            std::cout << "A character will not cipher by 1 by 1 matrix.. wired\n";
            std::_Exit(EXIT_FAILURE);
        }
    } catch (...) {
        std::cout << "Something wrong there ! " << std::endl;
    }
}
// namespace PolyGraphichCipher for avoid colition for future cipher
}

#endif
