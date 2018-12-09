//
// Created by human on 09.12.2018.
//
#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main()
{
    TestRunner tr;
    tr.RunTest([]
               {
                   ostringstream output;
                   PRINT_VALUES(output, 5, "red belt");
                   ASSERT_EQUAL(output.str(), "5\nred belt\n");
               }, "PRINT_VALUES usage example");

    tr.RunTest([]
               {
                   ostringstream output;
                   if (true)
                       PRINT_VALUES(output, 5, "red belt1");
                   ASSERT_EQUAL(output.str(), "5\nred belt1\n");
               }, "PRINT_VALUES usage example1");

    tr.RunTest([]
               {
                   ostringstream output;
                   if (false)
                       PRINT_VALUES(output, 5, "red belt1");
                   else
                       PRINT_VALUES(output, 5, "red belt2");
                   ASSERT_EQUAL(output.str(), "5\nred belt2\n");
               }, "PRINT_VALUES usage example2");

}