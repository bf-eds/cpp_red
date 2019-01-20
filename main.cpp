#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base constructor called." << endl;
    }

//    ~Base()
//    {
//        cout << "Base destructor called." << endl;
//    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived constructor called." << endl;
    }

    ~Derived()
    {
        cout << "Derived destructor called." << endl;
    }
};


int main()
{
//    Base b;
//    Derived d;
    array<char, 5> a = {"abcd"};
    string_view(&a[0], a.size());

    return 0;
}