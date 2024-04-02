/**
 * @file Solver.cpp
 *
 * @brief Solver class for solving quadratic and linear equations.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#include "Solver.h"

namespace slv
{
    Solver::Result Solver::solve(const long double aCoefficient, const long double bCoefficient, const long double cCoefficient)
    {
        if (aCoefficient != 0.0)
        {
            // Quadratic: ax^2 + bx + c = 0.
            // D = b^2 - 4ac.
            // In case of D < 0.0 no real roots exists,
            // Otherwise x1,x2 = (-b +- sqrt(D)) / 2a.
            // In both cases we can provide criticalPoint(-b/2a) and extremum(by putting criticalPoint into equation).
            const long double minusBCoefficient = -bCoefficient;
            const long double doubleACoefficient = 2 * aCoefficient;
            const long double criticalPoint = minusBCoefficient / doubleACoefficient;
            const long double extremum = aCoefficient * criticalPoint * criticalPoint + bCoefficient * criticalPoint + cCoefficient;

            if (const long double discriminant = bCoefficient * bCoefficient - 4 * aCoefficient * cCoefficient; discriminant < 0.0)
            {
                return QuadraticResult{ std::nullopt, extremum, criticalPoint };
            }
            else
            {
                const long double sqrtDiscriminant = sqrtl(discriminant);
                return QuadraticResult{
                    std::make_pair((minusBCoefficient - sqrtDiscriminant) / doubleACoefficient,
                                   (minusBCoefficient + sqrtDiscriminant) / doubleACoefficient),
                    extremum, criticalPoint
                };
            }
        }
        // Linear: bx + c = 0.
        // In case of b == 0 no root exist.
        // In case of b == 0 && c != 0 the equation is not correct.
        // In case of b == 0 && c == 0 the equation is an identity.
        // In case of b != 0, x = -c/b and extremum = x, at every point.
        return bCoefficient == 0.0 ? LinearResult{ std::nullopt } : LinearResult{ -cCoefficient / bCoefficient };
    }
} // namespace slv
