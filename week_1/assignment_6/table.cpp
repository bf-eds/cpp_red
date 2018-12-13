//
// Created by d.eroshenkov on 12.12.2018.
//

#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table

template<typename T>
class Table
{
public:
    Table(size_t rows, size_t columns)
    {
        Resize(rows, columns);
    }

    void Resize(size_t rows, size_t columns)
    {
        cells_.resize(rows);

        for (auto &row : cells_)
        {
            row.resize(columns);
        }
    }

    vector<T> &operator[](size_t idx)
    {
        return cells_[idx];
    }

    const vector<T> &operator[](size_t idx) const
    {
        return cells_[idx];
    }

    pair<size_t, size_t> Size() const
    {
        return {cells_.size(), cells_.empty() ? 0 : cells_[0].size()};
    }

private:
    vector<vector<T>> cells_;
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}