/**
 * @file Main.cpp
 *
 * @brief Main file for demonstration of work.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#include "Consumer.h"
#include "InputValidator.h"
#include "ParallelSolver.h"
#include "Producer.h"

int main(int argc, char* argv[])
{
    try
    {
        if (auto validatedInput = InputValidator::getValidatedInput(argc, argv))
        {
            slv::ParallelSolver pSolver;
            {
                // Creating thread-safe STL adapter (thread-safe queue) from non thread-safe original STL adapter.
                auto sharedContainer = mt::createThreadSafeSTLAdapterFrom(std::queue<std::vector<int>>{});
                // Producer and consumer instances will work with this sharedContainer.
                mt::Producer producer(sharedContainer);
                mt::Consumer consumer(sharedContainer, std::ref(pSolver));
                producer.enableWorkerThread();
                consumer.enableWorkerThread();
                producer.push({ std::move(validatedInput.value()) });
                // This sleep is necessary to prolong the life of the producer and consumer,
                // Otherwise after pushing validatedInput may not have time to get into sharedContainer.
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            std::cout << pSolver << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
    }
    system("pause");
}
