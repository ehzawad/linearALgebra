#include "Utilities.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

typedef double mType;

// prototypes
template <typename T>
T laplaceExpansion(util::Matrix<T> M);
template <typename T>
T findMinor(util::Matrix<T>& M, size_t row, size_t col);
template <typename T>
T expand(util::Matrix<T>& M, size_t col);

int main(int argc, char* argv[])
{
    const std::string msg = "Proper usage: \"MatrixDeterminant -f filename\" ";

    if (argc == 3) {
        if (std::string(argv[1]) == "-f") {
            std::ifstream inputFile(argv[2]);

            if (inputFile.is_open()) {
                size_t dimension;
                mType determinant{};
                // first value in the file == matrix dimension
                inputFile >> dimension;

                util::Matrix<mType> matrix = util::makeMatrix<mType>(dimension, dimension);

                // read matrix from file
                util::readMatrix(matrix, inputFile);

                std::cout << "M = " << std::endl;
                util::printMatrix(matrix);

                std::ofstream tmp("results.txt", std::ios_base::app);
                tmp << "M = " << std::endl;
                util::printMatrix(matrix, tmp);

                // LAPLACE EXPANSION
                determinant = laplaceExpansion(matrix);
                std::cout << "LaplaceExpansion::det(M) = " << determinant << std::endl;
                tmp << "LaplaceExpansion::det(M) = " << determinant << std::endl;

            }
            // couldn't open file specified as second parameter of program invocation
            else {
                std::cerr << "Couldn't open file : " << argv[2];
            }
        }
        // wrong first argument -> show error message
        else {
            std::cerr << msg;
        }
    } else {
        //@ todo = proccess keyboard input
        std::cerr << msg;
    }
}

template <typename T>
T laplaceExpansion(util::Matrix<T> M)
{
    T determinant{};

    if (M.size() == 1) {
        determinant = M[0][0];
    } else if (M.size() == 2) {
        determinant = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
    } else {
        determinant = expand(M, util::findBestColumn(M));
    }

    return determinant;
}

template <typename T>
T expand(util::Matrix<T>& M, size_t col)
{
    T determinant{};
    T sign{ 1 };

    for (size_t row = 0; row < M.size(); ++row) {
        if ((row + col) % 2 == 1) {
            sign = -1;
        } else {
            sign = 1;
        }

        if (!util::isZero(M[row][col])) {
            determinant += sign * M[row][col] * findMinor(M, row, col);
        }
    }

    return determinant;
}

template <typename T>
T findMinor(util::Matrix<T>& M, size_t row, size_t col)
{
    return laplaceExpansion(util::deleteRowAndColumn(M, row, col));
}
