#include "hillCipher.hpp"
#include "mathUtilities.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

typedef double mType;

int main(void)
{
    try {
        // MathUtility::VV matrix = MathUtility::makeMatrix(3, 3);
        // //
        // MathUtility::readMatrix(matrix, std::cin);
        //
        // MathUtility::VV F = MathUtility::findInverseMat(matrix);
        //
        // MathUtility::printMatrix(F);

        Hill Cipher;

        Cipher.statementToken();

        std::cout << std::endl;

        Cipher.decryptCode();
        std::cout << std::endl;

        std::flush(std::cout);
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
}
