/**
 * @file ParallelSolver.cpp
 *
 * @brief ParallelSolver class for solving quadratic and linear equations in parallel.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#include "ParallelSolver.h"

#include <sstream>
#include <future>

namespace slv
{
    std::vector<Solver::Result>
        ParallelSolver::BlockSolver::operator()(const std::vector<int>& coeffs, std::size_t first, const std::size_t last) const
    {
        std::vector<Solver::Result> result;
        result.reserve(last - first);
        while (first != last)
        {
            result.emplace_back(Solver::solve(coeffs[first], coeffs[first + 1], coeffs[first + 2])); // Passing a,b,c coefficients.
            first += 3; // 3 because a,b,c coefficients.
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const ParallelSolver& pSolver)
    {
        std::stringstream out;
        out.setf(std::ios::fixed);
        size_t currentIndex = 0;
        for (const std::vector<Solver::Result>& results : pSolver.m_results)
        {
            for (const Solver::Result& result : results)
            {
                out << "INPUT: (" << pSolver.m_coeffs[currentIndex] << ", "
                    << pSolver.m_coeffs[currentIndex + 1] << ", "
                    << pSolver.m_coeffs[currentIndex + 2] << ")\nOUTPUT: ";
                if (std::holds_alternative<Solver::LinearResult>(result))
                {
                    if (const Solver::LinearResult& r = std::get<Solver::LinearResult>(result))
                    {
                        out << '(' << r.value() << "). GLOBAL MIN(MAX) = " << r.value();
                    }
                    else
                    {
                        out << (pSolver.m_coeffs[currentIndex + 2] == 0 ? "AN IDENTITY" : "NOT CORRECT");
                    }
                }
                else
                {
                    const Solver::QuadraticResult& r = std::get<Solver::QuadraticResult>(result);
                    if (r.m_roots)
                    {
                        out << '(' << r.m_roots.value().first << ", " << r.m_roots.value().second << ')';
                    }
                    else
                    {
                        out << "NO REAL ROOTS";
                    }
                    out << ". GLOBAL " << (pSolver.m_coeffs[currentIndex] > 0 ? "MIN" : "MAX")
                        << " = " << r.m_extremum << " AT x = " << r.m_criticalPoint;
                }
                currentIndex += 3; // 3 because a,b,c coefficients.
                out << "\n\n";
            }
        }
        os << out.rdbuf();
        return os;
    }

    void ParallelSolver::operator()(std::vector<int> items)
    {
        m_coeffs = std::move(items);
        // At this point sz >= 3 && sz % 3 == 0. Validated by InputValidator.
        const std::size_t sz = m_coeffs.size();
        // minCoeffsCountPerThread must be chosen >= 3 && minCoeffsCountPerThread % 3 == 0.
        static constexpr std::size_t minCoeffsCountPerThread = 24;
        const std::size_t maxThreads = (sz + minCoeffsCountPerThread - 1) / minCoeffsCountPerThread;
        static const std::size_t hardwareThreads = std::jthread::hardware_concurrency();
        // In case of hardwareThreads == 0, the value 2 chosen hypothetically,
        // Taking into account that in this application 4 threads already can be started
        // (2 threads per consumer and 2 threads per producer).
        const std::size_t numThreads = std::min(hardwareThreads != 0 ? hardwareThreads : 2, maxThreads);
        // The work is divided almost equally between numThreads (except the last thread).
        const std::size_t blockSize = sz / numThreads / 3 * 3;
        const std::size_t numThreadsMinusOne = numThreads - 1;

        std::vector<std::future<std::vector<Solver::Result>>> futures(numThreadsMinusOne);
        // In case of exception or normal finish of execution threads will be automatically joined.
        std::vector<std::jthread> threads(numThreadsMinusOne);

        std::size_t blockStart = 0;
        for (std::size_t i = 0; i < numThreadsMinusOne; ++i)
        {
            std::size_t blockEnd = blockStart;
            blockEnd += blockSize; // every spawn thread will process blockSize coefficients.
            std::packaged_task<
                std::vector<Solver::Result>(
                    const std::vector<int>&, std::size_t, const std::size_t)> task(BlockSolver{});
            futures[i] = task.get_future();
            threads[i] = std::jthread(std::move(task), std::cref(m_coeffs), blockStart, blockEnd);
            blockStart = blockEnd;
        }

        m_results.resize(numThreads);
        for (std::size_t i = 0; i < numThreadsMinusOne; ++i)
        {
            m_results[i] = futures[i].get();
        }
        // The last portion of work done by current thread.
        m_results[numThreadsMinusOne] = BlockSolver{}(m_coeffs, blockStart, sz);
    }
} // namespace slv
