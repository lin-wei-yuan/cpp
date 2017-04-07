#include <iostream>
#include <vector>
using namespace std;

class D
{
    int i;
public:
    D(int _i) : i(_i) { cout << "D::D()" << endl; }
    ~D() { cout << "D::~D()" << endl; }
    void set(int _i) { i = _i;}
    int get() const { return i; }
};

ostream& operator<<(ostream& s, const D& obj)
{
    s << obj.get();
    return s;
}

void challenge0()
{
    int i = 10;
    int* pi = &i;

    cout << "pi = " << pi << ", *pi = " << *pi << ", size = " << sizeof(pi) <<  endl;
    cout << " size *pi =" << sizeof(*pi) << endl;

    delete pi;
}

void challenge1()
{
    D* p1 = new D(1);
    const D* p2 = new D(2);
    const D* const p3 = new D(3);
    D* const p4 = new D(4);

    // Compile error
    // p2->set(-2);
    // working
    p2 = p1;
    cout << p2->get() << endl;
    // compile error
    // p3 = p1;
    // p3->set(-3);
    // compile error
    // p4 = p1;
    p4->set(-4);
    cout << p4->get() << endl;

    delete p1;
    // delete p2;
    delete p3;
    delete p4;
}

void challenge2()
{
    D a[3] = {1, 2, 3};
    D* p = a;
    cout << *(p + 0) << endl;
    cout << *(p + 1) << endl;
    cout << *(p + 2) << endl;
}

int main()
{
    challenge2();
    return 0;
}
