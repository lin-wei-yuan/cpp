#include <iostream>
#include <memory>

class Test
{
public:
    Test() {}
    Test(int i_) : m_i(i_) {}
    int getID() const { return 1; }
private:
    int m_i;
};

// std::unique_ptr
void challenge1()
{
    std::unique_ptr<Test> u1{ new Test };
    // copy ctor in unique_ptr = delete
    // std::unique_ptr<Test> u2{ u1 };
    // Move rights to u2
    std::unique_ptr<Test> u2{ std::move( u1 ) };
    // Set or get data from ptr
    std::cout << "ID of u2 is " << (*u2).getID() << std::endl;
    std::cout << "ID of u2 is " << u2.get()->getID() << std::endl;
    std::cout << "ID of u2 is " << u2->getID() << std::endl;

    Test *t1 = new Test(1);
    std::unique_ptr<Test> u3{ t1 };
    // We dont have memory leak,
    // Now ``u3``s deleter will be called
    u3.reset();
    std::cout << " End of challenge1. Now all dtors will be called" << std::endl;
}

// std::shared_ptr
void challenge2()
{
    Test *t1 = new Test(1);
    std::shared_ptr<Test> s1{ t1 };
    std::cout << "Use count in s1: " << s1.use_count() << std::endl;
    std::shared_ptr<Test> s2{ s1 };
    std::cout << "Use count in s2: " << s2.use_count() << std::endl;
    // Move owner to a new shared ptr
    // s2 has 0 references
    std::shared_ptr<Test> s3{ std::move(s2) };
    std::cout << "Use count in s3: " << s3.use_count() << std::endl;
    if (!s2)
        std::cout << "s2 has 0 references" << std::endl;
}

// std::weak_ptr
struct B;
struct A
{
    A() { std::cout << "A()" << std::endl; }
    ~A() {  std::cout << "~A()" << std::endl; }
    std::shared_ptr<B> m_b;
};

struct B
{
    B() { std::cout << "B()" << std::endl; }
    ~B() {  std::cout << "~B()" << std::endl; }
    // Implementation with memory leak
    // std::shared_ptr<A> m_a;
    std::weak_ptr<A> m_a;
};

void challenge3()
{
    // shared_ptr race condition
    // A lock B
    // B lock A
    // So its a memory leak and A's and B's dtoc won't be called
    auto ao = std::make_shared<A>();
    ao->m_b = std::make_shared<B>();
    // when m_a is a weak_ptr, everything fine
    ao->m_b->m_a = ao;
}

int main(int argc, char const *argv[])
{
    challenge1();
    challenge2();
    challenge3();
    return 0;
}