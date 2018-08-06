#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <ctime>
#include <vector>
#include <queue>

std::string get_date()
{
    std::string s;
    auto t =  std::time(0);
    auto now = std::localtime(&t);
    return std::to_string(now->tm_hour) + ":" +
           std::to_string(now->tm_min) +  ":" +
           std::to_string(now->tm_sec / 10) +
           std::to_string(now->tm_sec % 10);
}

#define watch(x) std::cout << (#x) << " is " << x << std::endl
#define ts_log(x) std::cout << "[" << get_date() << "] " << x << std::endl;

#define WORKER_DELAY 5 // seconds
#define NETWORKS_COUNT 10 // seconds

struct Network
{
    std::string ssid;
    std::string password;
    int signal;
};

std::ostream& operator <<(std::ostream& ss, const Network& network)
{
    ss << std::to_string(network.signal) << "-" << network.ssid << "[" << network.password << "]";
    return ss;
}

class DataSource
{
public:
    Network GetRandomNetwork() const
    {
        // Generate some illusion of computing
        std::srand(std::time(nullptr));
        int component = std::rand() % 20 + 1;

        Network test;
        test.ssid = "test" + std::to_string(component);
        test.password = "test";
        test.signal = component;
        return test;
    }

    std::vector<Network> GetNetworkList() const
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::vector<Network> result;
        for (int i = 0; i < NETWORKS_COUNT; ++i)
        {
            result.push_back(GetRandomNetwork());
        }
        return result;
    }
};

class Worker
{
public:
    class IObserver
    {
    public:
        virtual void ReceiveNotification(const std::vector<Network> &network) = 0;
    };

    Worker(IObserver *observer)
        : m_observer(observer)
        , m_thread(&Worker::Loop, this)
        , m_notificating_data_condition(false)
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

    void NotificateData(bool enable)
    {
        // Updating flag after locking the same mutex
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_notificating_data_condition = enable;
        }

        m_cv.notify_all();
    }

    void Connect(const std::string ssid)
    {
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_preferred.push(ssid);
        }

        m_cv.notify_all();
    }

private:
    IObserver *m_observer;
    DataSource m_source;

    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    // Condition for unblocking
    bool m_notificating_data_condition;
    bool m_stop_condition;
    // Preffered networks
    std::queue<std::string> m_preferred;

    void Loop()
    {
        ts_log("[Worker::Loop] Loop started...");

        while (!m_stop_condition)
        {
            ts_log("[Worker::Loop] Iteraion...");

            bool _notification_cond = false;

            {
                std::lock_guard<std::mutex> lg(m_mutex);
                _notification_cond = m_notificating_data_condition;
            }

            // Sending info block
            if (_notification_cond)
            {
                ts_log("[Worker::Loop] Getting data");
                auto data = m_source.GetNetworkList();
                ts_log("[Worker::Loop] Notificating data");
                m_observer->ReceiveNotification(data);
            }

            // @TODO: Receive some events and respond

            //  Delay between operations
            {
                std::unique_lock<std::mutex> ul(m_mutex);
                // Calling wait_for without blocking or blocking with wrong mutex is UB
                m_cv.wait_for(ul, std::chrono::seconds(WORKER_DELAY), [&]
                {
                    // Getting value of notification and in case of positive result generate wakeup
                    if (m_notificating_data_condition)
                        ts_log("[Worker::Loop] Generate wakeup");
                    return m_stop_condition || m_notificating_data_condition;
                });
            }
        }
        ts_log("[Worker::Loop] Loop ends...");
    }
};

class Server : public Worker::IObserver
{
public:
    Server()
        : m_worker(this)
    {}

    virtual void ReceiveNotification(const std::vector<Network> &networks) override
    {
        ts_log("[Server::ReceiveNotification] Received networks: ");
        for(const auto& network: networks)
        {
            std::cout << network << std::endl;
        }
    }

    void StartNotificating()
    {
        m_worker.NotificateData(true);
    }

    void StopNotificating()
    {
        m_worker.NotificateData(false);
    }

    void SetNetworkToConnect(const std::string ssid)
    {
        m_worker.Connect(ssid);
    }

private:
    Worker m_worker;
};


int main(int argc, char const *argv[])
{
    Server s;

    while (true)
    {
        int data = -1;
        ts_log("[main] Type something: ");
        std::cin >> data;

        switch (data)
        {
        case 0:
            s.StopNotificating();
            break;
        case 1:
            s.StartNotificating();
            break;
        case -1:
            return 0;
        };
    }

    return 0;
}