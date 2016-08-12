#include "hillCipher.hpp"
#include "mathUtilities.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

typedef double mType;

int main(void)
{
    try {
        MathUtility::VV matrix = MathUtility::makeMatrix(3, 3);

        MathUtility::readMatrix(matrix, std::cin);

        double det = MathUtility::InverseOperation::laplaceExpansionDet(matrix);

        MathUtility::VV cofactorMat = MathUtility::InverseOperation::findCofactorMatrix(matrix);


        MathUtility::VV cofacMatT = MathUtility::InverseOperation::doTranspose(cofactorMat);

        MathUtility::printMatrix(cofactorMat);

        MathUtility::VV finalMat = MathUtility::InverseOperation::doInvertible(cofactorMat, det);

        MathUtility::printMatrix(finalMat);

        std::cout << std::endl;

        std::flush(std::cout);
    } catch (...) {
        std::cout << "Something unexpected !" << std::endl;
    }
}
