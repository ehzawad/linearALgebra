#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace util {
using V = std::vector<double>;
using VV = std::vector<V>;
// three dimensional vector
// using VVV = std::vector<VV>;
//
using oneD = std::vector<int>;
using twoD = std::vector<V>;
//

VV makeMatrix(int rows, int cols)
{
    VV temp(rows);
    for (auto& row : temp) {
        row.resize(cols);
    }

    return temp;
}

// If number is clouser enough to zero then like 0.00000000000001 set defaults to zero
// this is not strictly necessary

bool isZero(int number, double epsilon = 1e-12)
{
    return (number < epsilon) && (number > -epsilon);
}

// simple function for printing Matrix content to given output
// console is the default output
// printMatrix(M) -> prints Matrix M in the console
// printMatrix(M, std::ofstream("temp.txt")) -> print Matrix M in temp.txt file
// SIMILAR for read input

void printMatrix(const VV& matrix, std::ostream& output = std::cout)
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

void readMatrix(VV& matrix, std::istream& input = std::cin)
{
    for (auto& row : matrix) {
        for (auto& col : row) {
            input >> col;
        }
    }
}

//  function for finding column where 'value' repeats the most
// By default it seeks the column with the most amount of zeros
int findBestColumn(util::VV& M, int value = 0)
{
    // first = column index
    // second = number of 'value' occurrences
    std::pair<int, int> bestColumn{ 0, 0 };

    for (int i = 0; i < (int)M.size(); ++i) {
        int count{};
        for (int j = 0; j < (int)M.size(); ++j) {
            if (M[j][i] == value)
                count++;
        }

        if (count > bestColumn.second) {
            bestColumn.first = i;
            bestColumn.second = count;
        }
    }

    return bestColumn.first;
}

util::VV deleteRowAndColumn(util::VV M, int i, int j)
{
    // delete column ...as it is pointer to pointer
    for (int k = 0; k < (int)M.size(); ++k) {
        M[k].erase(M[k].begin() + j);
    }

    // pointer to that row
    M.erase(M.begin() + i);

    return M;
}

util::VV inputMatrix(std::string input)
{
    int row, col;
    std::cout << "Please enter row of " << input;
    std::cin >> row;
    std::cout << "please enter col of " << input;
    std::cin >> col;

    VV matrix = util::makeMatrix(row, col);

    util::readMatrix(matrix, std::cin);
    return matrix;
}

bool isMulPossible(const VV& matA, const VV& matB)
{
    return matA[0].size() == matB.size();
}

VV doMultiple(const VV& matA, const VV& matB)
{
    int multipleRow = matA.size();
    int multipleCol = matB[0].size();

    // initialize with value 0 in two dimentional matrices
    VV multiple(multipleRow, V(multipleCol, 0));

    for (int i = 0; i < (int)matA.size(); i++) {
        for (int k = 0; k < (int)matB[0].size(); k++) {
            for (int j = 0; j < (int)matB.size(); j++) {
                multiple[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }

    return multiple;
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

// making one dimentional row vector to two dimentional column vector
void dimensionVariant(V& oneD, size_t split)
{
    VV twoDPseudoTranpose(split, V(split, 0));

    for (size_t i = 0; i < split; i++) {
        for (size_t j = 0; j < 1; j++) {
            twoDPseudoTranpose[i][j] = engAlphabet(oneD[i]);
        }
    }

    std::cout << std::endl;

    printMatrix(twoDPseudoTranpose);
    std::cout << std::endl;
}

// http://stackoverflow.com/questions/30734787/c-2d-vector-convert-int-to-double
void twoDintToTwoDdouble(twoD& shit, VV& doubleShit)
{
    doubleShit.reserve(shit.size());
    for (auto&& v : shit) {
        doubleShit.emplace_back(std::begin(v), std::end(v));
    }
}

bool validate(const std::string& data, const std::string& expression)
{
    std::regex validationExpression = std::regex(expression);
    return regex_match(data, validationExpression);
}

std::string inputData(const std::string& fieldName, const std::string& expression)
{
    std::string data;

    std::cout << "Enter " << fieldName << ": ";
    getline(std::cin, data);

    // validate the data
    while (!(validate(data, expression))) {
        std::cout << "Invalid " << fieldName << ".\n";
        std::cout << "Enter " << fieldName << ": ";

        getline(std::cin, data);
    }
    return data;
}


// namespace End
}

#endif
