//
// Created by human on 06.01.2019.
//

#pragma once

#include <cstdlib>
#include <algorithm>

template<typename T>
class SimpleVector
{
public:
    SimpleVector() : begin_(nullptr), end_(nullptr), size_(nullptr)
    {
    }

    explicit SimpleVector(size_t size)
    {
        begin_ = new T[size];
        end_ = begin_ + size;
        size_ = end_;
    }

    ~SimpleVector()
    {
        delete[] begin_;
    }

    T &operator[](size_t index)
    {
        return begin_[index];
    }

    T *begin()
    {
        return begin_;
    }

    T *end()
    {
        return size_;
    }

    const T *begin() const
    {
        return begin_;
    }

    const T *end() const
    {
        return size_;
    }

    size_t Size() const
    {
        return size_ - begin_;
    }

    size_t Capacity() const
    {
        return end_ - begin_;
    }

    void PushBack(const T &value)
    {
        if (begin_ == nullptr)
        {
            begin_ = new T[1];
            end_ = begin_ + 1;
            size_ = end_;
            *begin_ = value;

            return;
        }
        else if (Size() == Capacity())
        {
            int capacity = Capacity();
            auto new_begin = new T[2 * capacity];
            auto new_end = new_begin + 2 * capacity;
            auto new_size = new_begin + capacity;

            std::copy(begin_, end_, new_begin);

            *new_size++ = value;

            delete[] begin_;

            begin_ = new_begin;
            end_ = new_end;
            size_ = new_size;
        }
        else
        {
            *size_++ = value;
        }
    }

private:
    T *begin_;
    T *end_;
    T *size_;
};


