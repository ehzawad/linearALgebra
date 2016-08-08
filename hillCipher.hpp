#include "Utilities.hpp"

class Hill {
public:
    int laplaceExpansion(util::VV M)
    {
        int determinant{};

        if (M.size() == 1) {
            determinant = M[0][0];
        } else if (M.size() == 2) {
            determinant = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
        } else {
            determinant = expand(M, util::findBestColumn(M));
        }

        return determinant;
    }

    int expand(util::VV& M, size_t col)
    {
        int determinant{};
        int sign{ 1 };

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

    util::VV allExpand(util::VV& M)
    {
        int cofactor{};
        int sign{ 1 };

        util::VV cofactorMatrix;

        for (size_t row = 0; row < M.size(); ++row) {
            for (size_t col = 0; col < M[0].size(); col++) {
                if ((row + col) % 2 == 1) {
                    sign = -1;
                } else {
                    sign = 1;
                }

                if (!util::isZero(M[row][col])) {
                    cofactor += sign * findMinor(M, row, col);
                    cofactorMatrix[row][col] = cofactor;
                }
            }
        }

        adjugateMat(cofactorMatrix);
        return cofactorMatrix;
    }

    util::VV adjugateMat(util::VV& A)
    {
        util::VV transpose;

        for (size_t row = 0; row < transpose.size(); ++row) {
            for (size_t col = 0; col < transpose[0].size(); col++) {
                transpose[row][col] = A[col][row];
            }
        }

        return transpose;
    }

    // Minors obtained by removing just one row and one column from square matrices (first minors){minor matrix}
    // are required for calculating matrix cofactors{cofactor matrix},
    // which in turn are useful for computing both the determinant and inverse of square matrices.

    int findMinor(util::VV& M, size_t row, size_t col)
    {
        return laplaceExpansion(util::deleteRowAndColumn(M, row, col));
    }
};
