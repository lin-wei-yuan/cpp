#include <iostream>
#include <functional>
#include <vector>

class TestContext
{
public:
    TestContext(int id)
        : m_id(id)
    {}

    void TestTask0()
    {
        std::cout << "Non-static method works! ID is " << m_id << std::endl;
    }

    void TestTask1(int some_param)
    {
        std::cout << "Non-static method works! ID is " << m_id << " param is " << some_param << std::endl;
    }

    static void TestTask2()
    {
        std::cout << "Static method works!" << std::endl;
    }

    static void TestTask3(void *ctx)
    {
        TestContext *pointer = static_cast<TestContext *>(ctx);
        int id = pointer->Get();
        std::cout << "Static method with ctx works! ID is " << id << std::endl;
    }

    int Get() const
    {
        return m_id;
    }

private:
    int m_id;
};

typedef std::function<void(void *)> TaskFunctor;
typedef std::vector<std::pair<TaskFunctor, void *>> TaskPool;

// Doesn't matter
/*static*/ void TestTaskOutside(void *ctx)
{
    TestContext *pointer = static_cast<TestContext *>(ctx);
    int id = pointer->Get();
    std::cout << "Static function with ctx works! ID is " << id << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<TestContext> tcs;
    for (int i = 0; i < 10; ++i)
        tcs.push_back(TestContext(i));

    TaskPool tp;

    std::function<void(TestContext &)> f0 = &TestContext::TestTask0;
    std::function<void(TestContext &, int)> f1 = &TestContext::TestTask1;
    std::function<void()> f2 = &TestContext::TestTask2;
    TaskFunctor f3 = &TestContext::TestTask3;
    TaskFunctor f4 = &TestTaskOutside;

    for (auto &tc : tcs)
        tp.push_back(std::make_pair(&TestContext::TestTask3, &tc));

    for (auto &func : tp)
        func.first(func.second);

    return 0;
}
