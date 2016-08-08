#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <iostream>
#include <vector>

namespace util {
using V = std::vector<int>;
using VV = std::vector<V>;
using VVV = std::vector<VV>;

template <typename T>
VV makeMatrix(size_t rows, size_t cols)
{
    VV temp(rows);
    for (auto& row : temp) {
        row.resize(cols);
    }

    return temp;
}

// If number is clouser enough to zero then like 0.00000000000001 set defaults to zero
// this is not strictly necessary

bool inline isZero(int number, double epsilon = 1e-12)
{
    return (number < epsilon) && (number > -epsilon);
}

// simple function for printing Matrix content to given output
// console is the default output
// printMatrix(M) -> prints Matrix M in the console
// printMatrix(M, std::ofstream("temp.txt")) -> print Matrix M in temp.txt file
// SIMILAR for read input

void inline printMatrix(const VV& matrix, std::ostream& output = std::cout)
{
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            output << col << " ";
        }
        output << std::endl;
    }
}

void inline readMatrix(VV& matrix, std::istream& input = std::cin)
{
    for (auto& row : matrix) {
        for (auto& col : row) {
            input >> col;
        }
    }
}

//  function for finding column where 'value' repeats the most
// By default it seeks the column with the most amount of zeros
size_t inline findBestColumn(util::VV& M, int value = 0)
{
    // first = column index
    // second = number of 'value' occurrences
    std::pair<size_t, size_t> bestColumn{ 0, 0 };

    for (size_t i = 0; i < M.size(); ++i) {
        size_t count{};
        for (size_t j = 0; j < M.size(); ++j) {
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

util::VV deleteRowAndColumn(util::VV M, size_t i, size_t j)
{
    // delete column ...as it is pointer to pointer
    for (size_t k = 0; k < M.size(); ++k) {
        M[k].erase(M[k].begin() + j);
    }

    // pointer to that row
    M.erase(M.begin() + i);

    return M;
}

util::VV inputMatrix(std::string input)
{
    size_t row, col;
    std::cout << "Please enter row of " << input;
    std::cin >> row;
    std::cout << "please enter col of " << input;
    std::cin >> col;

    VV matrix = util::makeMatrix<int>(row, col);

    util::readMatrix(matrix, std::cin);
    return matrix;
}

bool inline isMulPossible(const VV& matA, const VV& matB)
{
    return matA[0].size() == matB.size();
}

VV doMultiple(const VV& matA, const VV& matB)
{
    size_t multipleRow = matA.size();
    size_t multipleCol = matB[0].size();

    // initialize with value 0 in two dimentional matrices
    VV multiple(multipleRow, V(multipleCol, 0));

    for (size_t i = 0; i < matA.size(); i++) {
        for (size_t k = 0; k < matB[0].size(); k++) {
            for (size_t j = 0; j < matB.size(); j++) {
                multiple[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }

    return multiple;
}

// remember prime number always interger , so no need of template
// faster prime check, taken from stackoverflow.com
inline bool isPrime(unsigned int num)
{
    if (num <= 3) {
        return num > 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    } else {
        for (size_t i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

// namespace End
}

#endif
