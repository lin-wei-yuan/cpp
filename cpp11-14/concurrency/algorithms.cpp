#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <ctime>
#include <cmath>
#include <string>
#include <mutex>
#include <queue>

#include <defines.h>

#define UNIT_TESTING
#ifdef UNIT_TESTING
#include "gtest/gtest.h"
#endif

// #define BENCHMARKING
#ifdef BENCHMARKING
#include "benchmark/benchmark.h"
#endif

namespace algorithms
{

typedef unsigned long long                          ull;

// This method checks if candidate is prime number
bool IsPrime(ull candidate)
{
    if (candidate <= 2) return false;

    // @TODO: you can remove optiomization for longer tests
    // 3sec vs 27 ms in [0..100000] range
    // for(ull i = 2; i < candidate; ++i)
    for (ull i = 2; i < std::sqrt(candidate); ++i)
    {
        if (candidate % i == 0)
            return false;
    }

    return true;
}

} // end of algorithm namespace

namespace parallel
{

constexpr ull MAX_THREADS_COUNT = 8;
constexpr ull HW_THREAD_MULTIPLIER = 2;

typedef std::function<void(void *)>      TaskFunctor;
typedef std::pair<TaskFunctor, void *>   TaskPair;

class TaskPool
{
public:
    TaskPool()
        : m_thread(&TaskPool::MainLoop, this)
    {}

    ~TaskPool()
    {
        if (m_thread.joinable())
            m_thread.join();
    }

    void AddTask(const TaskFunctor &task, void *ctx)
    {
        std::lock_guard<std::mutex> _lock_guard(m_pool_mutex);
        m_task_queue.push(std::make_pair(task, ctx));
    }

    void CancelTasks()
    {
        std::lock_guard<std::mutex> _lock_guard(m_pool_mutex);

        while (m_task_queue.size() > 1)
            m_task_queue.pop();
    }

    TaskPool(const TaskPool &) = delete;
    TaskPool &operator=(const TaskPool &that) = delete;

private:
    std::queue<TaskPair> m_task_queue;
    std::thread m_thread;
    std::mutex m_pool_mutex;

    ull GetThreadsCount() const
    {
        const ull _hw_threads = std::thread::hardware_concurrency();
        return std::min(_hw_threads != 0 ? _hw_threads * HW_THREAD_MULTIPLIER
                        : HW_THREAD_MULTIPLIER, MAX_THREADS_COUNT);
    }

    void MainLoop()
    {
        while (true)
        {
            TaskPair _t;
            {
                std::lock_guard<std::mutex> lg(m_pool_mutex);

                if (m_task_queue.empty())
                    continue;

                _t = m_task_queue.front();
                m_task_queue.pop();
            }
            // Spawn thread
            std::thread worker([_t] ()
            {
                _t.first(_t.second);
            });
            worker.detach();
        }
    }
};
} // end of parallel namespace

//-------------------------------------------------------------------------------------//

#ifdef UNIT_TESTING

TEST(IsPrimeTesting, HandleRangeOfInput)
{
    EXPECT_EQ(algorithms::IsPrime(-1), false);
    EXPECT_EQ(algorithms::IsPrime(1), false);
    EXPECT_EQ(algorithms::IsPrime(2), false);
    EXPECT_EQ(algorithms::IsPrime(3), true);
    EXPECT_EQ(algorithms::IsPrime(5), true);
    EXPECT_EQ(algorithms::IsPrime(7), true);
}

class TestContext
{
public:
    TestContext()
        : m_test_data(1000000)
    {}

    static void TestTask(void *ctx)
    {
        TestContext *pointer = static_cast<TestContext *>(ctx);

        for (int i = 0; i < pointer->GetDataFromPulbic(); ++i)
            algorithms::IsPrime(i);

        std::cout << "End of " << std::this_thread::get_id() << " thread" << std::endl;
    }

    void MakeSomeNoise()
    {
        m_pool.AddTask(&TestTask, this);
    }

    int GetDataFromPulbic() const
    {
        return m_test_data;
    }
private:
    parallel::TaskPool m_pool;
    int m_test_data;
};

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    TestContext tc;

    for (int i = 0; i < 100; ++i)
        tc.MakeSomeNoise();

    return 0;
}

#elif defined BENCHMARKING

void IsPrime_Test(ull start, ull iterations)
{
    for (ull i = start; i < iterations; ++i)
        algorithms::IsPrime(i);
}

void Benchmark_IsPrime_1kkRange(benchmark::State &state)
{
    ull start_position = state.range(0);
    ull limit = state.range(1);

    while (state.KeepRunning())
        IsPrime_Test(start_position, limit);
}

BENCHMARK(Benchmark_IsPrime_1kkRange)->Unit(benchmark::kMillisecond)->Args({0, 100000});

BENCHMARK_MAIN()

#endif

