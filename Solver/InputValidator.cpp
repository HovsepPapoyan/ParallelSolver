/**
 * @file InputValidator.cpp
 *
 * @brief InputValidator class for command line arguments validation.
 *        Arguments must be int values, which represents coefficients
 *        of quadratic equations.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#include "InputValidator.h"

#include <charconv>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string_view>

std::optional<std::vector<int>> InputValidator::getValidatedInput(const int argc, const char* const argv[])
{
    if (argc < 4 || (argc - 1) % 3 != 0)
    {
        // Minimum 3 arguments are needed except the first one (program name).
        // Provided arguments count must be multiple of 3.
        std::cerr << "Please provide enough arguments\n";
        return std::nullopt;
    }
    std::vector<int> validatedInput;
    validatedInput.reserve(static_cast<std::size_t>(argc) - 1);
    for (const std::string_view arg : std::vector<std::string_view>(argv + 1, argv + argc))
    {
        int result;
        const char* const last = arg.data() + arg.size();
        auto [ptr, ec] = std::from_chars(arg.data(), last, result);

        if (ec != std::errc() || ptr != last
            || (result == 0 && arg.size() > 1) || (result != 0 && arg[0] == '0'))
        {            
            // reporting "is not an int" in case of diapason violation also. 
            std::cerr << std::quoted(arg) << " is not an int ["
                << std::numeric_limits<int>::min() << ',' << std::numeric_limits<int>::max() << "]\n";
            return std::nullopt;
        }
        validatedInput.push_back(result);
    }
    return validatedInput;
}
