/**
 * @file InputValidator.h
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

#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <optional>
#include <vector>

class InputValidator
{
public:
    static [[nodiscard]] std::optional<std::vector<int>> getValidatedInput(const int argc, const char* const argv[]);
};

#endif
