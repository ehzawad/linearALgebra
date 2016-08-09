#include "Utilities.hpp"
#include "linuxUtil.hpp"
#include <iomanip>
#include <stdexcept>
#include <string>

class Hill {
private:
    int detValue;
    std::string encryptText;

public:
    // setter and getter of string
    void setEncryptText(void)
    {
        termios process = linuxUtil::setNotEchoingMode();
        this->encryptText = util::inputData("message", ".+");
        linuxUtil::goBack(process);
    }

    std::string getEncryptText(void)
    {
        return this->encryptText;
    }

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

    void statementToken()
    {
        try {
            std::string vec = this->getEncryptText();
            size_t tokens{};
            size_t spaceFact{};

            if (vec.size() % 2 == 0) {
                tokens = vec.size() / 2;
                spaceFact = vec.size();
            } else if ((vec.size() % 2 != 0) && util::isPrime(vec.size())) {
                vec.resize(vec.size() + 1);
                tokens = (vec.size() / 2);
                spaceFact = vec.size();
            } else {
                tokens = vec.size() / 3;
                spaceFact = vec.size();
            }

            std::cout << "TOkensize : " << tokens << std::endl;

            size_t split{};

            if (spaceFact % 2 == 0) {
                split = 2;
            } else {
                split = 3;
            }

            util::VV twoD(tokens);

            for (size_t i = 0; i < tokens; i++) {
                std::copy_n(vec.begin(), split, std::back_inserter(twoD[i]));

                util::dimensionVariant(twoD[i], split);

                vec.erase(vec.begin(), vec.begin() + split);
            }
        } catch (...) {
            std::cout << "Something wrong there ! " << std::endl;
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

        std::cout << std::endl;
        util::printMatrixDouble(A);
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

        std::cout << std::endl;
        transpose(I);
    }

    // Minors obtained by removing just one row and one column from square matrices (first minors){minor matrix}
    // are required for calculating matrix cofactors{cofactor matrix},
    // which in turn are useful for computing both the determinant and inverse of square matrices.

    int findMinor(util::VV& M, int row, int col)
    {
        return laplaceExpansion(util::deleteRowAndColumn(M, row, col));
    }
};
