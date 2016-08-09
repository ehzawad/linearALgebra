#include "Utilities.hpp"
#include "hillCipher.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

typedef double mType;

// int main(int agrc, char* argv[])
int main(void)
{
    // Hill Class object
    Hill Cipher;

    // dimension which required for making matrix
    int matDimension{};
    Cipher.setDimension();
    matDimension = Cipher.getDimension();

    // allocating room for square Matrix
    // square matrix
    util::VV matrix = util::makeMatrix(matDimension, matDimension);

    // Should check command line argument vectors properly
    // otherwise program will send SEGV fault
    // std::ifstream inputFile((argv[1]));
    // you should check
    // if (inputFile.is_open()){
    //      util::readMatrix(matrix, inputFile);
    // }
    // else {
    // ....
    //     return -1;
    // }

    std::cout << "Please enter your Matrix, which will be used for encryption" << std::endl;

    util::readMatrix(matrix, std::cin);

    Cipher.setEncryptText();

    std::cout << Cipher.getEncryptText();

    std::cout << std::endl;

    Cipher.statementToken();

    mType determinant{};
    determinant = Cipher.laplaceExpansion(matrix);

    std::cout << std::endl;
}
