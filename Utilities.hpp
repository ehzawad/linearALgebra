#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include <vector>
#include <iostream>

namespace util{

template <typename ScalarType>
using Matrix = std::vector<std::vector<ScalarType>>;
/*
    returns matrix
*/
template <typename ScalarType>
Matrix<ScalarType> makeMatrix(size_t rows, size_t cols)
{
    Matrix<ScalarType> tmp(rows);
    for (auto& row : tmp)
    {
        row.resize(cols);
    }

    return tmp;
}
/*
    since we can't compare floating point numbers to 0 (zero),
    we'll check if they're in range close enough to zero
    (-epsilon, epsilon), where default epsilon=0,000000000001
*/
template <typename ScalarType>
bool inline isZero(ScalarType number, double epsilon = 1e-12)
{
    return (number < epsilon) && (number > -epsilon);
}
/*
    simple function for printing Matrix content to given output
    console is the default output
    printMatrix(M) -> prints Matrix M in the console
    printMatrix(M, std::ofstream("tmp.txt")) -> print Matrix M in tmp.txt file
*/
template <typename ScalarType>
void inline printMatrix(const Matrix<ScalarType>& matrix, std::ostream& output=std::cout)
{
    for (const auto& row : matrix)
    {
        for (const auto& col : row)
        {
            output << col << " ";
        }
        output << std::endl;
    }
}
/*
    simple function for populating Matrix from given input
    keyboard is the default input
    printMatrix(M) -> reads input from keyboard
    printMatrix(M, std::ifstream("tmp.txt")) -> reads Matrix M from tmp.txt file
*/
template <typename ScalarType>
void inline readMatrix( Matrix<ScalarType>& matrix, std::istream& input = std::cin)
{
    for (auto& row : matrix)
    {
        for (auto& col : row)
        {
            input >> col;
        }
    }
}

/*
    function for for swapping rows if given coefficient (matrix[row][col]) is equal to zero
    return true if there was non-zero coefficient below [row] in [column] and swap was succesful
    false otherwise
*/
template <typename ScalarType>
bool inline swapRows(util::Matrix<ScalarType>& matrix, size_t row, size_t col)
{
    for (size_t i = row + 1; i < matrix.size(); ++i)
    {
        if (!isZero(matrix[i][col]))
        {
            // found appropriate row -> swap rows and report success (true)
            std::swap(matrix[row], matrix[i]);
            return true;
        }
    }

    return false; //failed to find appropriate row to swap with
}

/*
    function for finding column where 'value' repeats the most
    By default it seeks the column with the most amount of zeros
*/
template <typename ScalarType>
size_t inline findBestColumn(util::Matrix<ScalarType>& M, ScalarType value = 0)
{
    // first = column index
    // second = number of 'value' occurrences
    std::pair<size_t, size_t> bestColumn{ 0, 0 };

    for (size_t i = 0; i < M.size(); ++i)
    {
        size_t count{};
        for (size_t j = 0; j < M.size(); ++j)
        {
            if (M[j][i] == value)
                count++;
        }

        if (count > bestColumn.second)
        {
            bestColumn.first = i;
            bestColumn.second = count;
        }
    }

    return bestColumn.first;
}
/*
    deletes row [i] and column [j] from matrix M
*/
template <typename ScalarType>
util::Matrix<ScalarType> deleteRowAndColumn(util::Matrix<ScalarType> M, size_t i, size_t j)
{
    // delete column j
    for (size_t k = 0; k < M.size(); ++k)
    {
        M[k].erase(M[k].begin() + j);
    }
    // delete row i
    M.erase(M.begin() + i);

    return M;
}


}

#endif // end of header guard
