//
// Created by human on 09.12.2018.
//

#include <string>
#include <vector>
using namespace std;

#define VAR(a, b) a ## b
#define VAR1(a, b) VAR(a, b)
#define UNIQ_ID VAR1(var, __LINE__)

int main()
{
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}