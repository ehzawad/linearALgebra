#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

#include "inputValidate.hpp"
#include "linuxUtil.hpp"
#include "mathUtilities.hpp"
#include <climits>
#include <iomanip>
#include <stdexcept>
#include <string>

class Hill {
private:
    std::string encryptText;

public:
    // setter and getter of string
    void setEncryptText(void)
    {
        termios process = linuxUtil::setNotEchoingMode();
        this->encryptText = ValidateInput::inputData("message", ".+");
        linuxUtil::goBack(process);
    }

    // get encryptText text
    std::string getEncryptText(void)
    {
        return this->encryptText;
    }


    void splittingOnTheFly(MathUtility::VV twoD, std::string& vec, size_t tokens, size_t split)
    {
        for (size_t i = 0; i < tokens; i++) {
            std::copy_n(vec.begin(), split, std::back_inserter(twoD[i]));

            MathUtility::dimensionVariant(twoD[i], split);

            vec.erase(vec.begin(), vec.begin() + split);
        }
    }

    void tokeniner(std::string& vec)
    {
        size_t tokens{};
        size_t spaceFact{};

        if (vec.size() % 2 == 0) {
            tokens = vec.size() / 2;
            spaceFact = vec.size();
        } else if ((vec.size() % 2 != 0) && MathUtility::isPrime(vec.size())) {
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

        MathUtility::VV twoD(tokens);

        splittingOnTheFly(twoD, vec, tokens, split);
    }

    void statementToken()
    {
        try {

            std::string vec = this->getEncryptText();
            tokeniner(vec);

        } catch (...) {
            std::cout << "Something wrong there ! " << std::endl;
        }
    }

};

#endif
