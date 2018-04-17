#include <iostream>
// use std::hash
#include <functional>
#include <unordered_set>
#include <limits>
using namespace std;

template<typename S, typename F>
void hash_combine(S &seed, const F &field)
{
    seed ^= (std::hash<F> {}(field) << 1);
}

struct SData
{
public:
    uint8_t field1;
    uint16_t field2;
    uint32_t field3;
    uint64_t field4;
    std::string field5;
};

bool operator==(const SData &o1, const SData &o2)
{
    return o1.field1 == o2.field1 &&
           o1.field2 == o2.field2 &&
           o1.field3 == o2.field3 &&
           o1.field4 == o2.field4 &&
           o1.field5 == o2.field5;
}

namespace std
{

template<> // means specialization
struct hash<SData>
{
    typedef SData arg_t;
    typedef std::size_t res_t;

    res_t operator()(const arg_t &s) const
    {
        res_t seed;
        hash_combine(seed, s.field1);
        hash_combine(seed, s.field2);
        hash_combine(seed, s.field3);
        hash_combine(seed, s.field4);
        hash_combine(seed, s.field5);
        return seed;
    }
};
}

int main(int argc, char const *argv[])
{
    SData s3{ 1, 0, 0, 0, "Hi! Some hash for you" };
    SData s1{ 0, 0, 0, 0, "00" };
    SData s2{ 0, 0, 0, 1, "00" };

    std::unordered_set<SData> dataset = { s1, s2, s3 };
    auto hasher = dataset.hash_function();

    for (const auto &data : dataset)
        std::cout << "Hash: " << hasher(data) << std::endl;

    std::cout << std::boolalpha << "Is in set: " << (dataset.find(s1) != dataset.end()) << std::endl;

    return 0;
}