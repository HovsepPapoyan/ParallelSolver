/**
 * @file ParallelSolver.h
 *
 * @brief ParallelSolver class for solving quadratic and linear equations in parallel.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#ifndef PARALLEL_SOLVER_H
#define PARALLEL_SOLVER_H

#include "Solver.h"

#include <iostream>
#include <vector>

namespace slv
{
    class ParallelSolver
    {
        // Each worker thread generates collection of results by
        // Executing operator() for BlockSolver instance.
        struct BlockSolver
        {
            [[nodiscard]] std::vector<Solver::Result> operator()(const std::vector<int>& coeffs, std::size_t first, const std::size_t last) const;
        };

    public:
        void operator()(std::vector<int> items);

    private:
        friend std::ostream& operator<<(std::ostream& os, const ParallelSolver& pSolver);

    private:
        std::vector<int> m_coeffs; // Vector of coefficients from input (a1, b1, c1, a2, b2, c2, ...).
        std::vector<std::vector<Solver::Result>> m_results; // Every element represents work done by one thread.
    };
} // namespace slv

#endif
