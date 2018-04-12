#include <print.h>

template<typename T>
struct greater_than
{
    bool operator() (const T& l, const T& r) const
    {
        return l > r;
    }
};

void challenge()
{
    int numbers[] = { 1, 3, 2, 4, 5, 5, 4, 3, 2, 1 };
    std::set<int>  s1(numbers, numbers + 10);
    print<std::set<int> >(s1);
    std::cout << s1.size() << std::endl;
    // O(logn)
    std::cout << s1.count(2) << std::endl;
    // O(logn)
    std::set<int>::iterator search = s1.find(3);

    if (search != s1.end())
    {
        std::cout << (*search) << std::endl;
    }

    else
    {
        std::cout << "not found!" << std::endl;
    }

    // insert overloads
    std::pair<std::set<int>::iterator, bool> result = s1.insert(6);
    // std::pair<it, bool>
    std::cout << (*result.first) << ", " << result.second << ", " << std::distance(s1.begin(), result.first) << std::endl;
    print<std::set<int> >(s1);
    // O(1) if before of after result.first, else O(logn)
    std::set<int>::iterator it = s1.insert(result.first, 8);
    std::cout << (*it) << std::endl;
    // STL comparer
    std::set<int, std::greater<int> > s2 (numbers, numbers + 10);
    print<std::set<int, std::greater<int> > >(s2);
    // Custom comparer
    std::set<int, greater_than<int> > s3 (numbers, numbers + 10);
    print<std::set<int, greater_than<int> > >(s3);
}

int main()
{
    challenge();
    return 0;
}
