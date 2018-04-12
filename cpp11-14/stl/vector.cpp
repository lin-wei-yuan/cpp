#include <print.h>

/* Vector */
void challenge()
{
    // O(1)
    std::vector<int> v1;
    print<std::vector<int> >(v1);
    // O(n), linear in count
    std::vector<int> v2(10, 1);
    print<std::vector<int> >(v2);
    // O(n), linear in count
    std::vector<int> v3(10);
    print<std::vector<int> >(v3);
    // O(n), linear in v3.size
    std::vector<int> v4(v3);
    print<std::vector<int> >(v4);
    // O(n), linear in distance between begin and end
    std::vector<int> v5(v3.begin(), v3.end());
    print<std::vector<int> >(v5);
    // Accessors
    // O(n), linear in count
    std::vector<int> v6(10, 5);
    print<std::vector<int> >(v6);
    // O(n), linear in size of v6
    std::vector<int> v7 = v6;
    print<std::vector<int> >(v7);
    // O(n), linear in count
    std::vector<int> v8;
    v8.assign(10, 5);
    print<std::vector<int> >(v8);
    // O(n), linear in distance between begin and end
    v8.assign(v2.begin(), v2.end());
    print<std::vector<int> >(v8);
    // O(1), const
    int index = v8.at(0);
    std::cout << index << std::endl;
    // Return reference
    v8.at(0) = 9;

    // Generate std::out_of_range
    try
    {
        std::cout << v8.at(v8.size()) << std::endl;
    }

    catch (const std::out_of_range& e)
    {
        std::cout << e.what() << std::endl;
    }

    // No bounds checking is performed
    v8[0] = 1;
    // SF
    // v8[v8.size()] = 1;
    print<std::vector<int> >(v8);

    // Iterators
    for (std::vector<int>::iterator it =  v8.begin(); it != v8.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    for (std::vector<int>::const_iterator it =  v8.begin(); it != v8.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    for (std::vector<int>::reverse_iterator it =  v8.rbegin(); it != v8.rend(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
    std::cout << v8.capacity() << ", " << v8.size() << std::endl;
    v8.reserve(11); // capacity = 11, size = 10
    v8.push_back(1); // capacity = 11, size = 11
    v8.push_back(1);  // capacity = 22(previous capacity x2), size = 11
    std::cout << v8.capacity() << ", " << v8.size() << std::endl;
    print<std::vector<int> >(v8);
    // Linear in the difference between the current size and count.
    v8.resize(5, 10);
    std::cout << v8.capacity() << std::endl;
    std::cout << v8.size() << std::endl;
    print<std::vector<int> >(v8);
    // Modifiers
    int numbers[] = { 1, 2, 3, 4, 5 };
    std::vector<int> v9(numbers, numbers + 5);
    // O(1 + dist(it, end))
    v9.insert(v9.end(), 6);
    print<std::vector<int> >(v9);
    // SF
    // v9.erase(v9.end());
    // O(n), linear in dist(it)
    v9.erase(v9.end() - 1);
    print<std::vector<int> >(v9);
    // Amortized O(1)
    v9.push_back(10);
    print<std::vector<int> >(v9);
    // O(1)
    v9.pop_back();
    // O(1)
    std::cout << v9.front() << std::endl;
    // O(1)
    std::cout << v9.back() << std::endl;
}

int main()
{
    challenge();
    return 0;
}
