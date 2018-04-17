#include <iostream>
#include <vector>
#include <cassert>
#include <typeinfo>

#include "./include/vector.h"

static int index = 0;

class A
{
public:
    A()
    {
        std::cout << "A::A()" << std::endl;
        set();
    }
    A(A &&that)
    {
        std::cout << "Move A::A()" << std::endl;
        set();
    }
    A(const A &that)
    {
        std::cout << "Copy A::A()" << std::endl;
        set();
    }
    ~A()
    {
        std::cout << "A::~A()" << std::endl;
        set();
    }

    A &operator=(const A &that)
    {
        std::cout << "Copy A::operator=" << std::endl;
        return *this;
    }
    A &operator=(A &&that)
    {
        std::cout << "Copy A::operator=" << std::endl;
        return *this;
    }

    int i() const
    {
        return m_i;
    }
    void set()
    {
        m_i = ++index;
    }
private:
    int m_i;
};

std::ostream &operator<<(std::ostream &oin, const A &obj)
{
    oin << obj.i();
    return oin;
}

template<typename T>
void print(const T &container)
{
    std::cout << std::endl;
    std::cout << "Typename " << typeid(container).name() << std::endl;
    std::cout << "Container: size[" << container.size() << "]";
    std::cout << " capacity[" << container.capacity() << "]" << std::endl;
    std::cout << "Elements: " << std::endl;

    if (container.size() == 0)
    {
        std::cout << "Empty" << std::endl;
        return;
    }

    std::cout << "By index : ";

    for (size_t i = 0; i < container.size(); ++i)
        std::cout << container[i] << " ";

    std::cout << std::endl << "Iterator : ";

    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

template<typename T, typename X>
void unit(const T &c1, const X &c2)
{
    static int test_id = 1;
    assert(c1.size() == c2.size());
    assert(c1.capacity() == c2.capacity());

    if (c1.size() > 0)
        assert(*(c1.begin()) == *(c2.begin()));

    for (size_t i = 0; i < c1.size(); ++i)
        assert(c1.at(i) == c2.at(i));

    std::cout << "=---------------------------=" << std::endl;
    std::cout << "#" << test_id << " Passed!" << std::endl;
    print<T>(c1);
    print<X>(c2);
    std::cout << "=---------------------------=" << std::endl;
    test_id++;
}

// comparison of vec and std::vector ctors
void challenge0()
{
    custom::vector<int> v0;
    std::vector<int> stl_v0;
    unit(v0, stl_v0);
    custom::vector<int> v1(5);
    std::vector<int> stl_v1(5);
    unit(v1, stl_v1);
    custom::vector<int> v2(4, 101);
    std::vector<int> stl_v2(4, 101);
    unit(v2, stl_v2);
    custom::vector<int> v3(v1);
    std::vector<int> stl_v3(stl_v1);
    unit(v3, stl_v3);
    custom::vector<int> v4(v2.begin(), v2.end());
    std::vector<int> stl_v4(stl_v2.begin(), stl_v2.end());
    unit(v4, stl_v4);
}

void challenge1()
{
    A tmp;
    // custom::vector<A> test(2, tmp);
    std::vector<A> stl_test(2, tmp);
}

int main()
{
    challenge0();
    // challenge1();
    return 0;
}
