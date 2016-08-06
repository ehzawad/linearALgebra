#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <iostream>
#include <vector>

namespace util {

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> makeMatrix(size_t rows, size_t cols)
{
    Matrix<T> temp(rows);
    for (auto& row : temp) {
        row.resize(cols);
    }

    return temp;
}

// If number is clouser enough to zero then like 0.00000000000001 set defaults to zero

template <typename T>
bool inline isZero(T number, double epsilon = 1e-12)
{
    return (number < epsilon) && (number > -epsilon);
}

// simple function for printing Matrix content to given output
// console is the default output
// printMatrix(M) -> prints Matrix M in the console
// printMatrix(M, std::ofstream("temp.txt")) -> print Matrix M in temp.txt file
// SIMILAR for read input

template <typename T>
void inline printMatrix(const Matrix<T>& matrix, std::ostream& output = std::cout)
{
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            output << col << " ";
        }
        output << std::endl;
    }
}

template <typename T>
void inline readMatrix(Matrix<T>& matrix, std::istream& input = std::cin)
{
    for (auto& row : matrix) {
        for (auto& col : row) {
            input >> col;
        }
    }
}

//  function for finding column where 'value' repeats the most
// By default it seeks the column with the most amount of zeros
template <typename T>
size_t inline findBestColumn(util::Matrix<T>& M, T value = 0)
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

template <typename T>
util::Matrix<T> deleteRowAndColumn(util::Matrix<T> M, size_t i, size_t j)
{
    // delete column ...as it is pointer to pointer
    for (size_t k = 0; k < M.size(); ++k) {
        M[k].erase(M[k].begin() + j);
    }

    // pointer to that row
    M.erase(M.begin() + i);

    return M;
}

template <typename T>
util::Matrix<T> inputMatrix(std::string input)
{
    size_t row, col;
    std::cout << "Please enter row of " << input;
    std::cin >> row;
    std::cout << "please enter col of " << input;
    std::cin >> col;

    util::Matrix<double> matrix = util::makeMatrix<double>(row, col);

    util::readMatrix(matrix, std::cin);
    return matrix;
}

template <typename T>
bool inline isMulPossible(const Matrix<T>& matA, const Matrix<T>& matB)
{
    return matA[0].size() == matB.size();
}

template <typename T>
Matrix<T> doMultiple(const Matrix<T>& matA, const Matrix<T>& matB)
{
    size_t multipleRow = matA.size();
    size_t multipleCol = matB[0].size();

    // initialize with value 0 in two dimentional matrices
    util::Matrix<double> multiple(multipleRow, std::vector<double>(multipleCol, 0));

    for (size_t i = 0; i < matA.size(); i++) {
        for (size_t k = 0; k < matB[0].size(); k++) {
            for (size_t j = 0; j < matB.size(); j++) {
                multiple[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }

    return multiple;
}

// namespace End
}

#endif
