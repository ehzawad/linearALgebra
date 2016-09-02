#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

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
    bool flagToDecrypt = true;
    // user input text
    std::string inputText;
    // store encrypted code string
    MathUtility::VV encryptedCodeString;
    // store decrypted code string
    MathUtility::VV decryptedCodeString;

    // keyMatrix and it's inverseKeyMatrix too !
    MathUtility::VV keyMatrix{};
    MathUtility::VV inverseKeyMatrix{};
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
    MathUtility::VV onlyEncrypt(MathUtility::VV&, size_t);
    void onlyDecrypt(void);
    // on the fly, it will encipher and decipher the text
    void splittingOnTheFly(std::string&);
    // just tokenize the whole string
    void tokenizer(std::string&);
    // will call the tokenizer method
    void doEncrypt(void);

    // this is directly store encrypted code
    void encryptedCodeStorage(MathUtility::VV&);
    // this is directly store decrypted code
    void decryptedCodeStorage(MathUtility::VV&);

    void printEncryptedCode(void);
    void printDecryptedCode(void);
};

// namespace PolyGraphichCipher for avoid collition for future cipher
}

#endif
