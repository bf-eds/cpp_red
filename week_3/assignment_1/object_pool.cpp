//
// Created by human on 06.01.2019.
//

#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template<class T>
class ObjectPool
{
public:
    T *Allocate()
    {
        if (!deallocated_.empty())
        {
            auto object = deallocated_.front();
            allocated_.insert(object);
            deallocated_.pop();
            return object;
        }
        else
        {
            auto new_object = new T;
            allocated_.insert(new_object);
            return new_object;
        }
    }

    T *TryAllocate()
    {
        if (!deallocated_.empty())
        {
            return Allocate();
        }
        else
        {
            return nullptr;
        }
    }

    void Deallocate(T *object)
    {
        if (allocated_.find(object) == allocated_.end())
        {
            throw invalid_argument("");
        }

        deallocated_.push(object);
        allocated_.erase(object);
    }

    ~ObjectPool()
    {
        for (auto item : allocated_)
        {
            delete item;
        }

        while (!deallocated_.empty())
        {
            delete deallocated_.front();
            deallocated_.pop();
        }
    }

private:
    set<T *> allocated_;
    queue<T *> deallocated_;
};

void TestObjectPool()
{
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}