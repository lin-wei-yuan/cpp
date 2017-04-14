#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <ctime>
#include <string>

#include <defines.h>

using utils::CaptureTime;

typedef std::chrono::time_point<std::chrono::system_clock> t_point;
typedef unsigned long long ull;

class scoped_guard
{
public:
    scoped_guard() { std::cout << "Thread #" << std::this_thread::get_id() << " started." << std::endl; }
    ~scoped_guard() { std::cout << "Thread #" << std::this_thread::get_id() << " finished." << std::endl; }
};

namespace parallel
{
    constexpr ull operations_per_thread = 25;

    ull get_num_of_threads(ull operations)
    {
        const ull max_threads = operations / operations_per_thread;
        const ull hw_threads = std::thread::hardware_concurrency();
        return std::min(hw_threads != 0 ? hw_threads : 2, max_threads);
    }

    template< typename It, typename T>
    struct acc
    {
        void operator()(It first, It last, T& initial)
        {
            scoped_guard sg;
            initial = std::accumulate(first, last, initial);
        }
    };

    template< typename It, typename T>
    T accumulate(It first, It last, T initial)
    {
        const ull length = std::distance(first, last);
        if(length == 0)
        {
            return initial;
        }
        const ull threads_count = get_num_of_threads(length);
        const ull block_size = length / threads_count;
        // Create thread pool
        std::vector<std::thread> pool(threads_count - 1);
        std::vector<T> results(threads_count, 0);
        It block_start = first;
        for(ull i = 0; i < threads_count - 1; ++i)
        {
            It block_end = block_start;
            std::advance(block_end, block_size);
            pool.at(i) = std::thread(acc<It, T>(), block_start, block_end, std::ref(results.at(i)));
            block_start = block_end;
        }
        std::for_each(pool.begin(), pool.end(), std::mem_fn(&std::thread::join));
        acc<It, T>()(block_start, last, std::ref(results.at(threads_count -1)));
        acc<decltype(results.begin()), T>()(results.begin(), results.end(), std::ref(initial));
        return initial;
    }
} // end of parallel namespace

/*
    Results on 8 cores( 8 hardware threads)
    [accumulate] Non-parallel version time is 609ms. Result is 1000000000
    [accumulate] Parallel version time is 242ms. Result is 1000000000
    On 1 thread
    [accumulate] Non-parallel version time is 601ms. Result is 1000000000
    [accumulate] Parallel version time is 650ms. Result is 1000000000
*/
int main(int argc, char const *argv[])
{
    CaptureTime<std::chrono::milliseconds> ct;
    std::vector<ull> v(100000000, 10);
    // std version, non parallel
    ct.Start();
    auto sum_non_parallel = std::accumulate(v.begin(), v.end(), 0);
    auto time_non_parallel = ct.Stop();
    std::cout << "[accumulate] Non-parallel version time is " << time_non_parallel
              << "ms. Result is " << sum_non_parallel << std::endl;
    // parallel version
    ct.Start();
    auto sum_parallel = parallel::accumulate(v.begin(), v.end(), 0);
    auto time_parallel = ct.Stop();
    std::cout << "[accumulate] Parallel version time is " << time_parallel
              << "ms. Result is " << sum_parallel << std::endl;

    return 0;
}