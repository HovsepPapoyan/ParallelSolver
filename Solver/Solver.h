/**
 * @file Solver.h
 *
 * @brief Solver class for solving quadratic and linear equations.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <optional>
#include <variant>

namespace slv
{
    class Solver
    {
    public:
        struct QuadraticResult
        {
            std::optional<std::pair<long double, long double>> m_roots;
            long double m_extremum;
            long double m_criticalPoint;
        };
        using LinearResult = std::optional<long double>;
        using Result = std::variant<LinearResult, QuadraticResult>;
        static [[nodiscard]] Result solve(const long double aCoefficient, const long double bCoefficient, const long double cCoefficient);
    };
} // namespace slv

#endif
