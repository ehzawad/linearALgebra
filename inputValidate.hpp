#ifndef _VALIDATE_INPUT_HPP
#define _VALIDATE_INPUT_HPP

#include <iostream>
#include <regex>
#include <string>
#include <string>

namespace ValidateInput {

inline bool validate(const std::string& data, const std::string& expression)
{
    std::regex validationExpression = std::regex(expression);
    // if input data does not match with user defined regex
    // then function will return false
    return std::regex_match(data, validationExpression);
}

inline std::string inputData(const std::string& fieldName, const std::string& expression)
{
    std::string data;

    std::cout << "Enter " << fieldName << " : ";
    getline(std::cin, data);

    // validate the data
    // while loop will execute until user input does not match with regular expression
    while (!(validate(data, expression))) {
        std::cout << "Invalid " << fieldName << ".\n";
        std::cout << "Enter " << fieldName << ": ";

        // input with space or /r
        getline(std::cin, data);
    }
    return data;
}
// end ValidateInput namespace
}

#endif
