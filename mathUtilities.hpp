#ifndef _MATHMathUtility_HPP_
#define _MATHMathUtility_HPP_

#include "inputValidate.hpp"
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
// macro
#define ONECOLUMN 1

namespace MathUtility {
using V = std::vector<double>;
using VV = std::vector<V>;
// three dimensional vector
// using VVV = std::vector<VV>;

std::string dimension;
//
using oneD = std::vector<int>;
using twoD = std::vector<V>;

void setDimension(void)
{
    dimension = ValidateInput::inputData("dimension", "\\d+");
}

int getDimension(void)
{
    return std::stoi(dimension);
}

MathUtility::VV makeMatrix(int rows, int cols)
{
    VV temp(rows);
    for (auto& row : temp) {
        row.resize(cols);
    }

    return temp;
}

// If number is clouser enough to zero then like 0.00000000000001 set defaults to zero
// this is not strictly necessary

bool isZero(double number, double epsilon = 1e-12)
{
    return (number < epsilon) && (number > -epsilon);
}

// simple function for printing Matrix content to given output
// console is the default output
// printMatrix(M) -> prints Matrix M in the console
// printMatrix(M, std::ofstream("temp.txt")) -> print Matrix M in temp.txt file
// SIMILAR for read input

void printMatrix(const MathUtility::VV& matrix, std::ostream& output = std::cout)
{
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            output << std::setw(3) << col << " ";
        }
        output << std::endl;
    }
}

// same as printMatrix, just for double with precison
void printMatrixDouble(const VV& matrix, std::ostream& output = std::cout)
{
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            output << std::setprecision(3);
            output << std::setw(10);
            output << col << " ";
        }

        output << std::endl;
    }
}

// reading input from console or other file stream
void readMatrix(MathUtility::VV& matrix, std::istream& input = std::cin)
{
    for (auto& row : matrix) {
        for (auto& col : row) {
            input >> col;
            if (input.fail()) {
                std::cin.clear(); // reset the failed state
                std::_Exit(EXIT_FAILURE);
            }
        }
    }

    // http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
    // Ignore to the end of line , flushing std::cin in c++ way
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//  function for finding column where 'value' repeats the most
// By default it seeks the column with the most amount of zeros
int findBestColumn(MathUtility::VV& M, double value = 0)
{
    // first = column index
    // second = number of 'value' occurrences
    std::pair<double, double> bestColumn{ 0, 0 };

    for (int i = 0; i < (int)M.size(); ++i) {
        int count{};
        for (int j = 0; j < (int)M.size(); ++j) {
            if (M[j][i] == value) {
                count++;
            }
        }

        if (count > bestColumn.second) {
            bestColumn.first = i;
            bestColumn.second = count;
        }
    }

    return bestColumn.first;
}

MathUtility::VV deleteRowAndColumn(MathUtility::VV M, int i, int j)
{
    // delete column ...as it is pointer to pointer
    for (int k = 0; k < (int)M.size(); ++k) {
        M[k].erase(M[k].begin() + j);
    }

    // pointer to that row
    M.erase(M.begin() + i);

    return M;
}

bool isMulPossible(VV& matA, VV& matB)
{
    return matA[0].size() == matB.size();
}

MathUtility::VV doMultiple(MathUtility::VV& matA, MathUtility::VV& matB)
{
    // multipleRow comes from column of first matrixA
    size_t multipleRow = matA.size();
    // multipleCol comes from row of second matrixB
    size_t multipleCol = matB[0].size();

    // initialize with value 0 in two dimentional matrices
    // initialize matrix is strictly necessary
    VV multipleM(multipleRow, V(multipleCol, 0));

    if (MathUtility::isMulPossible(matA, matB)) {
        // performing multiplication
        for (size_t m = 0; m < matA.size(); m++) {
            for (size_t i = 0; i < matB[0].size(); i++) {
                // step hold for sum of two corresponding elements
                for (size_t j = 0; j < matB.size(); j++) {
                    multipleM[m][i] += matA[m][j] * matB[j][i];
                }
            }
        }
    }

    return multipleM;
}

// remember prime number always interger , so no need of template
// faster prime check, taken from stackoverflow.com
bool isPrime(int num)
{
    if (num <= 3) {
        return num > 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    } else {
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

// converting englist letters to corresponding number
// required for hill cipher or other cipher like ceaser cipher
// A - 1
// B - 1
// .... Z - 26
// also same for small letters
//
int engAlphabet(const char character)
{
    if (std::isalpha(character) && std::isupper(character)) {
        return (character - 'A' + 1);
    } else if (std::isalpha(character) && std::islower(character)) {
        return (character - 'a' + 1);
    } else {
        return 0;
    }
}

MathUtility::VV dimensionVariantReturn(MathUtility::V& oneD, size_t split)
{
    MathUtility::VV pseudoTranpose(split, V(split, 0));

    for (size_t i = 0; i < split; i++) {
        for (size_t j = 0; j < ONECOLUMN; j++) {
            pseudoTranpose[i][j] = engAlphabet(oneD[i]);
        }
    }

    return pseudoTranpose;
}

void dimensionVariantPrint(MathUtility::VV& pseudoVector, size_t split)
{
    for (size_t i = 0; i < split; i++) {
        for (size_t j = 0; j < ONECOLUMN; j++) {
            std::cout << pseudoVector[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// making one dimentional row vector to two dimentional column vector
void dimensionVariant(MathUtility::V& oneD, size_t split)
{
    VV PseudoTranpose(split, V(split, 0));

    for (size_t i = 0; i < split; i++) {
        for (size_t j = 0; j < ONECOLUMN; j++) {
            PseudoTranpose[i][j] = engAlphabet(oneD[i]);
        }
    }

    std::cout << std::endl;

    MathUtility::dimensionVariantPrint(PseudoTranpose, split);
}

// http://stackoverflow.com/questions/30734787/c-2d-vector-convert-int-to-double
void twoDintToTwoDdouble(MathUtility::twoD& shit, MathUtility::VV& doubleShit)
{
    doubleShit.reserve(shit.size());
    for (auto&& v : shit) {
        doubleShit.emplace_back(std::begin(v), std::end(v));
    }
}

// as some mutual recursion happening here
// function declaration is not hoisting like JS
// forward declaration is necessary here
// Findind Inverse Matrix
namespace InverseOperation {
    // here is not passing reference , be careful
    int laplaceExpansionDet(MathUtility::VV M);

    // but here all matrix are passed by reference
    int findMinor(MathUtility::VV& M, int row, int col);
    int expand(MathUtility::VV& M, int col);
    MathUtility::VV doTranspose(MathUtility::VV& A);
    MathUtility::VV doInvertible(MathUtility::VV& I, double);

    // Minors obtained by removing just one row and one column from square matrices (first minors){minor matrix}
    // are required for calculating matrix cofactors{cofactor matrix},
    // which in turn are useful for computing both the determinant and inverse of square matrices.

    int findMinor(MathUtility::VV& M, int row, int col)
    {
        return InverseOperation::laplaceExpansionDet(MathUtility::deleteRowAndColumn(M, row, col));
    }

    int expand(MathUtility::VV& M, int col)
    {
        int determinant{};

        for (int row = 0; row < (int)M.size(); ++row) {
            int sign = ((row + col) % 2 == 1) ? -1 : 1;

            if (!MathUtility::isZero(M[row][col])) {
                determinant += sign * M[row][col] * InverseOperation::findMinor(M, row, col);
            }
        }
        return determinant;
    }

    int laplaceExpansionDet(MathUtility::VV M)
    {
        int determinant{};

        if (M.size() == 1) {
            determinant = M[0][0];
        } else if (M.size() == 2) {
            determinant = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
        } else {
            determinant = InverseOperation::expand(M, MathUtility::findBestColumn(M));
        }

        return determinant;
    }

    MathUtility::VV findCofactorMatrix(MathUtility::VV& M)
    {
        int cofactor{};

        int size = M.size();

        MathUtility::VV cofactorMatrix(size, MathUtility::V(size, 0));

        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; col++) {
                int sign = ((row + col) % 2 == 1) ? -1 : 1;

                cofactor = sign * findMinor(M, row, col);
                std::cout << "cofactor " << cofactor << std::endl;
                cofactorMatrix[row][col] = cofactor;
            }
        }

        return cofactorMatrix;
    }

    MathUtility::VV doTranspose(MathUtility::VV& A)
    {
        int size = A.size();

        for (int row = 0; row < size - 1; ++row) {
            for (int col = row + 1; col < size; col++) {
                std::swap(A[row][col], A[col][row]);
            }
        }

        return A;
    }

    MathUtility::VV doInvertible(MathUtility::VV& I, double detValue)
    {
        if (detValue == 0) {
            throw std::overflow_error("Divide by zero exception");
        } else {

            int size = I.size();

            MathUtility::VV adj(size, MathUtility::V(size, 0.00));

            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; col++) {
                    adj[row][col] += (double)(I[row][col] * (1.00 / (double)detValue));
                }
            }

            return adj;
        }
    }
}

MathUtility::VV findInverseMat(MathUtility::VV& matrix)
{
    double det = MathUtility::InverseOperation::laplaceExpansionDet(matrix);
    MathUtility::VV cofactorMat = MathUtility::InverseOperation::findCofactorMatrix(matrix);
    MathUtility::VV cofacMatT = MathUtility::InverseOperation::doTranspose(cofactorMat);
    MathUtility::VV finalMat = MathUtility::InverseOperation::doInvertible(cofactorMat, det);

    return finalMat;
}

// namespace End
}

#endif
