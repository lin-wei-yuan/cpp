#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <forward_list>
#include <stdexcept>

namespace {

template<typename T>
void print(const T& container)
{
    if (container.empty())
    {
        std::cout << "Empty!" << std::endl;
        return;
    }

    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *(it) << " ";
    }

    std::cout << std::endl;
}

} // end of unnamed namespace