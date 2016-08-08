#include "Utilities.hpp"
#include <stdexcept>
#include <iomanip>

class Hill {
private:
    int detValue;

public:
    void setDeterminantValue(int detValue)
    {
        this->detValue = detValue;
    }

    int getDeterminantValue(void)
    {
        if (this->detValue == 0) {
            return -1;
        } else {
            return this->detValue;
        }
    }

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

    int expand(util::VV& M, int col)
    {
        int determinant{};
        int sign{ 1 };

        for (int row = 0; row < (int)M.size(); ++row) {
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

    void allExpand(util::VV& M)
    {
        int cofactor{};
        int sign{ 1 };

        int size = M.size();

        util::VV cofactorMatrix(size, util::V(size, 0));

        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; col++) {
                if ((row + col) % 2 == 1) {
                    sign = -1;
                } else {
                    sign = 1;
                }

                if (!util::isZero(M[row][col])) {
                    cofactor = sign * findMinor(M, row, col);
                    cofactorMatrix[row][col] = cofactor;
                }
            }
        }

        adjugateMat(cofactorMatrix);
    }

    void transpose(util::VV A)
    {

        int size = A.size();

        for (int row = 0; row < size - 1; ++row) {
            for (int col = row + 1; col < size; col++) {
                std::swap(A[row][col], A[col][row]);
            }
        }

        util::printMatrix(A);
        std::cout << std::endl;
    }

    void adjugateMat(util::VV& A)
    {

        util::printMatrix(A);

        invertible(A);
        std::cout << std::endl;
    }

    void invertible(util::VV& I)
    {
        int size = I.size();

        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; col++) {
                I[row][col] = I[row][col] / (double)(getDeterminantValue());
            }
        }

        transpose(I);
        std::cout << std::endl;
    }

    // Minors obtained by removing just one row and one column from square matrices (first minors){minor matrix}
    // are required for calculating matrix cofactors{cofactor matrix},
    // which in turn are useful for computing both the determinant and inverse of square matrices.

    int findMinor(util::VV& M, int row, int col)
    {
        return laplaceExpansion(util::deleteRowAndColumn(M, row, col));
    }
};
