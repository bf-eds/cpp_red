#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
    {
        return;
    }

    vector<typename RandomIt::value_type> sorted = move(
            vector<typename RandomIt::value_type>(move_iterator<RandomIt>(range_begin),
                                                  move_iterator<RandomIt>(range_end)));

    auto third = (range_end - range_begin) / 3;
    auto second_third = range_begin + third;
    auto third_third = range_begin + third * 2;

    MergeSort(range_begin, second_third);
    MergeSort(second_third, third_third);
    MergeSort(third_third, range_end);

    vector<typename RandomIt::value_type> tmp;
    merge(move_iterator(range_begin), move_iterator(second_third), move_iterator(second_third),
          move_iterator(third_third), back_inserter(tmp));
    merge(move_iterator(tmp.begin()), move_iterator(tmp.end()), move_iterator(third_third), move_iterator(range_end),
          range_begin);

}

struct NoncopyableInt
{
    int value;

    NoncopyableInt(const NoncopyableInt &) = delete;
    NoncopyableInt &operator=(const NoncopyableInt &) = delete;

    NoncopyableInt(NoncopyableInt &&) = default;
    NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
    return lhs.value == rhs.value;
}

bool operator<(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
    return lhs.value < rhs.value;
}

void TestIntVector()
{
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void TestAvoidsCopying()
{
    vector<NoncopyableInt> numbers;
    numbers.push_back({6});
    numbers.push_back({1});
    numbers.push_back({3});
    numbers.push_back({9});
    numbers.push_back({1});
    numbers.push_back({9});
    numbers.push_back({8});
    numbers.push_back({12});
    numbers.push_back({11});

    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}