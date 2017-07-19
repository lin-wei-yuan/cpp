#include <iostream>
using namespace std;

class Node
{
public:
    Node()
    : i (123)
    , s("Test string")
    {}

    ~Node() {}

    int GetValue() const { return i; }

private:
    int i;
    string s;
    friend class List; // its no necessary if its public or private
};

class List
{
public:
    List(Node& obj)
    : n(obj)
    {}

    void PrintNode() const
    {
        std::cout << n.i << " " << n.GetValue() << " " << n.s << endl;
    }
private:
    Node& n;
};

int main(int argc, char const *argv[])
{
    Node n;
    List l(n);
    l.PrintNode();
    return 0;
}