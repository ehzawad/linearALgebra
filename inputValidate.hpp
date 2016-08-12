#ifndef _VALIDATE_INPUT_HPP
#define _VALIDATE_INPUT_HPP

#include <iostream>
#include <regex>
#include <string>
#include <string>

namespace ValidateInput {

bool validate(const std::string& data, const std::string& expression)
{
    std::regex validationExpression = std::regex(expression);
    return std::regex_match(data, validationExpression);
}

std::string inputData(const std::string& fieldName = " ", const std::string& expression = " ")
{
    std::string data = " ";

    std::cout << "Enter " << fieldName << " : ";
    getline(std::cin, data);

    // validate the data
    while (!(validate(data, expression))) {
        std::cout << "Invalid " << fieldName << ".\n";
        std::cout << "Enter " << fieldName << ": ";

        getline(std::cin, data);
    }
    return data;
}
// end ValidateInput namespace
}

#endif
