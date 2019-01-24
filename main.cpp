#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// Numbers can be validated before being passed through the math functions.
// Does not validate if strings contain random characters that aren't numbers.
// Division & squareRoot will return the floor of the number.
// SquareRoot is done by the long division method. Youtube : https://www.youtube.com/watch?v=R7Vgk9D8xMo
// Does only positive numbers - may have many bugs. But they're my sexy bugs, though.
// This assumes that the strings are all numbers.
// Probably should rename it to BigUnsignedInt, but ¯\_(ツ)_/¯
namespace BigInt
{
    const std::string add(const std::string &, const std::string &);
    const std::string subtract(const std::string &, const std::string &);
    const std::string multiply(const std::string &, const std::string &);
    const std::string divide(const std::string &, const std::string &);
    const std::string square(std::string &);
    const std::string squareRoot(const std::string &);

    // put these separately in something or something
    void validateNumber(std::string &);
    void initiateRemoveZerosDestructionSequence(std::string &);

    // comparison functions
    bool isStrictlyGreaterThan(const std::string &, const std::string &);
    bool isStrictlyLessThan(const std::string &, const std::string &);

    // for sqrt function
    const std::string findClosestPerfectSquare(const std::string &);

    // for the divide function
    const std::string findQuotient(const std::string &, const std::string &);

}; // namespace - BigInt utility 

//////////////////////////////////////////////////////////////////////////////
/////                       some functions                               /////
//////////////////////////////////////////////////////////////////////////////

void BigInt::validateNumber(std::string &a)
{
    if (a.front() == '0' && a.length() > 1)
    { initiateRemoveZerosDestructionSequence(a); }
}// validateNumbers

void BigInt::initiateRemoveZerosDestructionSequence(std::string &str)
{
    auto lastZeroPos = str.find_first_not_of("0");
    if (lastZeroPos != std::string::npos)
    {
        str.erase(str.begin(), str.begin() + lastZeroPos);
        if (str.empty())
        { str = "0"; }
    }
    else
    {
        string = "0";
    }
}// initiateRemoveZeroesDestructionSequence

//////////////////////////////////////////////////////////////////////////////
/////                       compare functions                            /////
//////////////////////////////////////////////////////////////////////////////

bool BigInt::isStrictlyGreaterThan(const std::string &a, const std::string &b)
{
    if (a.size() > b.size())
    { return true; }
    else if (a.size() < b.size())
    { return false; }

    auto itrA = a.begin();
    auto itrB = b.begin();

    while (itrA != a.end())
    {
        char x = *itrA - '0';
        char y = *itrB - '0';

        if (x > y)
        { return true; }
        if (x < y)
        { return false; }

        ++itrA;
        ++itrB;
    }// while - since we assume both strings are of same length, we only need to check if one of them hits the end.

    return false;
}// isStrictlyGreaterThan - is a > b ? --- negation: a <= b 

bool BigInt::isStrictlyLessThan(const std::string &a, const std::string &b)
{
    if (a.size() < b.size())
    { return true; }
    else if (a.size() > b.size())
    { return false; }

    auto itrA = a.begin();
    auto itrB = b.begin();

    while (itrA != a.end())
    {
        char x = *itrA - '0';
        char y = *itrB - '0';

        if (x > y)
        { return false; }
        if (x < y)
        { return true; }

        ++itrA;
        ++itrB;
    }// while - since we assume both strings are of same length, we only need to check if one of them hits the end.

    return false;
}// isStrictlyLessThan - is a < b ? --- negation: a >= b

//////////////////////////////////////////////////////////////////////////////
/////                       find functions                               /////
//////////////////////////////////////////////////////////////////////////////

const std::string BigInt::findClosestPerfectSquare(const std::string &n)
{
    std::string num = n;
    BigInt::validateNumber(num); // removes the zero at the front if there is one
    std::vector<std::string> pSquare = {"0", "1", "4", "9", "16", "25", "36", "49", "64", "81",
                                        "100"}; // 100 is only needed to backtrack if n > 81
    for (int i = 0; i < pSquare.size(); ++i)
    {
        if (BigInt::isStrictlyGreaterThan(pSquare[i], num))
        {
            return std::to_string(i - 1);
        }// if
    }// for
    return "ERR: PERFECT SQUARE NOT FOUND"; // should not hit
}// findClosestPerfectSquare - used for the squareRoot function --- only finds the first 10 perfect sqs

const std::string BigInt::findQuotient(const std::string &divisor, const std::string &dividend)
{
    if (divisor.empty() || dividend.empty())
    { return "ERR: PARAMETERS MISSING NUMBERS"; }
    if (BigInt::isStrictlyGreaterThan(divisor, dividend))
    { return "ERR: divisor > dividend"; }

    char q = 1;
    std::string quotient = "1";
    std::string product = divisor;

    do
    {
        ++q;
        quotient = std::to_string(q);
        product = BigInt::multiply(quotient, divisor);
    }
    while (!BigInt::isStrictlyGreaterThan(product, dividend));
    --q;
    quotient = std::to_string(q);
    return quotient;
}// findQuotient - used for the division function.

//////////////////////////////////////////////////////////////////////////////
/////                       math functions                               /////
//////////////////////////////////////////////////////////////////////////////

const std::string BigInt::add(const std::string &first, const std::string &second)
{
    //if(first.empty() || second.empty()) { return "ERR: ADD - PARAMETERS MISSING NUMBERS"; }
    if (!BigInt::isStrictlyGreaterThan(first, second))
    {
        return add(second, first);
    }// if first < second, just call add and swap first and second

    std::string result = "";
    char carryOver = 0;
    auto itrSecond = second.rbegin();
    for (auto itrFirst = first.rbegin(); itrFirst != first.rend(); ++itrFirst)
    {
        char a = *itrFirst - '0';
        char b = 0;
        if (itrSecond != second.rend())
        {
            b = *itrSecond - '0';
            ++itrSecond;
        }// if

        char sum = (a + b) + carryOver;
        if (sum > 9)
        {
            carryOver = 1;
            sum -= 10;
        }// if
        else
        {
            carryOver = 0;
        }// else

        result += std::to_string(sum);
    }// for
    if (carryOver == 1)
    { result += std::to_string(carryOver); }
    std::reverse(result.begin(), result.end());
    return result;
}// add - order of inputs don't matter.

const std::string BigInt::subtract(const std::string &first, const std::string &second)
{
    //if(first.empty() || second.empty()) { return "ERR: SUBTRACT - PARAMETERS MISSING NUMBERS"; }

    if (first == second)
    { return "0"; }
    if (BigInt::isStrictlyLessThan(first, second))
    {
        return "ERROR : SUBTRACT - CAN'T COMPUTE NEGATIVE RESULT.";
    }

    std::string result = "";
    char carryOver = 0;
    auto itrSecond = second.rbegin();
    for (auto itrFirst = first.rbegin(); itrFirst != first.rend(); ++itrFirst)
    {
        char a = *itrFirst - '0' - carryOver;
        char b = 0;
        if (itrSecond != second.rend())
        {
            b = *itrSecond - '0';
            ++itrSecond;
        }

        char difference = 0;
        if (a < b)
        {
            a += 10;
            difference = a - b;
            carryOver = 1;
        }
        else
        {
            difference = a - b;
            carryOver = 0;
        }

        result += std::to_string(difference);
    }// for itrFirst
    std::reverse(result.begin(), result.end());
    BigInt::validateNumber(result); // get rid of zeros infront of result
    return result;
}// subtract - order matters. (first - second) and first >= second

const std::string BigInt::multiply(const std::string &first, const std::string &second)
{
    if (first.empty() || second.empty())
    { return "ERR: MULT - PARAMETERS MISSING NUMBERS"; }
    if (first == "0" || second == "0")
    { return "0"; }
    unsigned int zeroes = 0; // this means we can't mult 2 numbers with both more than 2^32 digits
    std::string curr = "";
    for (auto itrFirst = first.rbegin(); itrFirst != first.rend(); ++itrFirst)
    {
        char carryOver = 0;
        char ia = *itrFirst - '0';
        std::string resultant = std::string(zeroes, '0');

        for (auto itrSecond = second.rbegin(); itrSecond != second.rend(); ++itrSecond)
        {
            char ib = *itrSecond - '0';
            char mult = (ia * ib) + carryOver;

            if (mult > 9)
            {
                carryOver = mult / 10;
                mult = mult % 10;
            }// if
            else
            {
                carryOver = 0;
            }// else

            resultant += std::to_string(mult);
        }// for str second
        if (carryOver > 0)
        { resultant += std::to_string(carryOver); }

        std::reverse(resultant.begin(), resultant.end());
        curr = add(resultant, curr); // input's order doesn't matter
        ++zeroes;
    }// for str first

    return curr;
}// multiply - order doesn't matter i think

const std::string BigInt::divide(const std::string &dividend, const std::string &divisor)
{
    if (dividend.empty() || divisor.empty())
    { return "ERR: DIVIDE - MISSING NUMBERS IN PARAMETERS"; }
    if (divisor == "0")
    { return "ERR: DIVIDING BY ZERO --- INITIATE BLACK HOLE OF DOOM"; }
    if (dividend == "0")
    { return "0"; }
    if (BigInt::isStrictlyLessThan(dividend, divisor))
    { return "0"; }

    std::string currentDividend = "";
    std::string quotient = "";

    for (const auto &digit : dividend)
    {
        if (currentDividend.front() == '0' && digit == '0')
        {
            quotient += "0"; // nothing divides so tack on a zero
        }
        else if (currentDividend.front() == '0' && digit != '0')
        {
            currentDividend = std::to_string(
                    digit - '0'); // starts with a zero but next digit isn't so set it to that digit
        }
        else
        {
            currentDividend += std::to_string(digit - '0'); // just appends with new digit
        }

        if (!BigInt::isStrictlyGreaterThan(divisor, currentDividend))
        {
            std::string quotientDigit = BigInt::findQuotient(divisor, currentDividend);
            std::string product = BigInt::multiply(divisor, quotientDigit);
            currentDividend = BigInt::subtract(currentDividend, product);
            quotient += quotientDigit;
        }
        else if (quotient.size() > 0 && currentDividend != "0")
        {
            quotient += "0";
            // eliminates cases such as 92/3 returns 3 (should be 30) or 920/3 returns 36 ( should be 306).
            // also 40/2 returns 200 (should be 20)
        }
    }// for - b/c i am looking at the digits starting from the left, i can use this cool version of the for loop
    return quotient;
}// divide - read as (dividend / divisor) i.e : (x / y).

const std::string BigInt::square(std::string &a)
{
    if (a == "0" || a.empty())
    { return "0"; }
    return multiply(a, a);
}// square - it's just multiply(a,a)

const std::string BigInt::squareRoot(const std::string &a)
{
    std::string num = a;
    if (num.size() & 1)
    {
        std::reverse(num.begin(), num.end());
        num += "0";
        std::reverse(num.begin(), num.end());
    }// if - size is of odd length insert a zero in the beginning

    auto itrNum = num.begin();
    const std::string TEN = "10";
    const std::string ONE = "1";
    const std::string TWO = "2";
    std::string currDividend = std::to_string(*itrNum - '0') + std::to_string(*(itrNum + 1) - '0');
    std::string ans = BigInt::findClosestPerfectSquare(currDividend);

    std::string divisor = BigInt::multiply(ans, TWO);
    divisor = BigInt::multiply(divisor, TEN);

    std::string diff = BigInt::square(ans);
    currDividend = BigInt::subtract(currDividend, diff);
    itrNum += 2;

    for (; itrNum != num.end(); itrNum += 2)
    {
        currDividend += std::to_string(*itrNum - '0') + std::to_string(*(itrNum + 1) - '0');
        BigInt::validateNumber(currDividend); // gets rid of leading zeroes
        for (int i = 0; i <= 10; ++i)
        {
            std::string iStr = std::to_string(i);
            diff = BigInt::add(divisor, iStr);
            diff = BigInt::multiply(diff, iStr);

            if (BigInt::isStrictlyGreaterThan(diff, currDividend) || i == 10)
            {
                iStr = BigInt::subtract(iStr, ONE);

                diff = BigInt::add(divisor, iStr);
                diff = BigInt::multiply(diff, iStr);

                currDividend = BigInt::subtract(currDividend, diff);
                ans += iStr;

                divisor = BigInt::add(divisor, iStr);
                divisor = BigInt::add(divisor, iStr);
                divisor = BigInt::multiply(divisor, TEN);
                break;
            }// if
        }// divisor s.t (divisor + i)*i <= currDividend
    }// for
    return ans;
}// squareRoot - squareRoot is computed by the long divison method
// Youtube : https://www.youtube.com/watch?v=R7Vgk9D8xMo

//////////////////////////////////////////////////////////////////////////////
/////                       codewars part                                /////
//////////////////////////////////////////////////////////////////////////////

/* 
Test cases that broke my thing, but it is fine now...i think:
integer_square_root("160063593978312608452035430196648684522819963582241909605399894233829238970843") 
ans: "400079484575643554020218053610093368412"
integer_square_root("1648958910898087425494") 
ans: "40607375080"
integer_square_root("527786092180402773503647") 
ans: "726488879598"
integer_square_root("23232328323215435345345345343458098856756556809400840980980980980809092343243243243243098799634") 
ans:"152421548093487868711992623730429930751178496967"
integer_square_root("12323309809809534545458098709854808654685688665486860956865654654654324238000980980980") 
ans: "3510457208086937291253621317073222057793129"
Test cases that don't work VS2017
integer_square_root("0010") 
ans: "3"
*/

std::string integer_square_root(std::string number)
{
    // Coding and coding ...
    BigInt::validateNumber(number);
    return BigInt::squareRoot(number);
}// integer_square_root