#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


template<typename It>
struct IteratorRange
{
    It first, last;

    IteratorRange(It begin, It end) : first(begin), last(end)
    {
    }
};

template<typename T>
auto MakeRange(T &container)
{
    return IteratorRange(container.begin(), container.end());
}

int main()
{
    IteratorRange vs_rng(10, 23);
    const string s = "Hello, world!";
    IteratorRange<string::const_iterator> rng = MakeRange(s);
    string ss = "Hello, world!";
    auto rng1 = MakeRange(ss);
    return 0;
}
