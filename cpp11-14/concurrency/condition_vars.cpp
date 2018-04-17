#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace test {}

class Worker
{
public:
    Worker()
        : m_thread(&Worker::Loop, this)
        , m_data(false)
        , m_stop_condition(false)
    {}

    ~Worker()
    {
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_stop_condition = true;
        }

        m_cv.notify_all();

        if (m_thread.joinable())
            m_thread.join();
    }

    void Notifier()
    {
        // Updating flag after locking the same mutex
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_data = true;
        }

        m_cv.notify_all();
    }

private:
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    // Condition for unblocking
    bool m_data;
    bool m_stop_condition;

    void Loop()
    {
        while (!m_stop_condition)
        {
            std::cout << "Working on some shit..." << std::endl;

            {
                std::unique_lock<std::mutex> ul(m_mutex);
                // Calling wait_for without blocking or blocking with wrong mutex is UB
                m_cv.wait_for(ul, std::chrono::seconds(5), [&]
                {
                    bool tmp = m_data;
                    m_data = !m_data;
                    return tmp || m_stop_condition;
                });
            }
        }
        std::cout << "End loop..." << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Worker w;

    while (true)
    {
        int data = -1;
        std::cout << "Type something: ";
        std::cin >> data;
        if (data == 5)
            w.Notifier();
        if (data == 0)
            break;
    }

    return 0;
}