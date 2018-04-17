#include <print.h>

/* List */
void challenge()
{
    int numbers[] = { 1, 2, 3, 4, 5 };
    std::list<int> l1(numbers, numbers + 5);
    print<std::list<int> >(l1);
    std::list<int> l2;

    for (int i = 0; i < 10; ++i)
        l2.push_back(i);

    print<std::list<int> >(l2);

    for (int i = 0; i < 10; ++i)
        l2.push_front(i);

    print<std::list<int> >(l2);

    for (int i = 0; i < 10; ++i)
        l2.pop_front();

    print<std::list<int> >(l2);

    for (int i = 0; i < 10; ++i)
        l2.pop_back();

    print<std::list<int> >(l2);
    std::list<int> l3 (numbers, numbers + 5);
    // O(1)
    l3.erase(l3.begin());
    print<std::list<int> >(l3);
    // O(n), n = distance(begin, end)
    l3.erase(l3.begin(), l3.end());
    print<std::list<int> >(l3);
    // List operations
    std::list<int> l4 (numbers, numbers + 5);
    std::list<int> l5 (numbers, numbers + 5);
    // O(size() + size() - 1)
    l4.merge(l5);
    print<std::list<int> >(l4);
    print<std::list<int> >(l5); // Empty
    std::list<int> l6 (numbers, numbers + 5);
    print<std::list<int> >(l6);
    // O(n)
    l6.reverse();
    print<std::list<int> >(l6);
    // O(nlog(n))
    l6.sort();
    print<std::list<int> >(l6);
    print<std::list<int> >(l4);
    // O(n)
    l4.unique();
    print<std::list<int> >(l4);
}


int main()
{
    challenge();
    return 0;
}
