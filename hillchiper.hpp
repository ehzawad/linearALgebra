#include "Utilities.hpp"

class Hill {
public:
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
};
