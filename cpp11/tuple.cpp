#include <iostream>
#include <tuple>

// Let's create container that might be contains different types
class CVariant
{
public:
    // @TODO: at
    // @TODO: at const
    // @TODO: push_back
    // @TODO: push_front
    // @TODO: size

    template<typename ... Args>
    void push_back( Args ... values)
    {
        auto m_packer_ex = std::tuple_cat( m_packer, std::make_tuple( values ... ) );
        std::cout << m_packer_ex.tuple_size() << std::endl;
    }

    template<typename T>
    T at( size_t index )
    {
        // return std::get<0>( m_packer );
        return (T)0;
    }

private:
    std::tuple<> m_packer;
};

void challenge1()
{
    CVariant v;
    v.push_back( 1, 2, 3, 4 );
    std::cout << " Element:" << v.at<int>( 0 ) << std::endl;
}

int main(int argc, char const *argv[])
{
    challenge1();
    return 0;
}