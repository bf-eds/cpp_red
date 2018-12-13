//
// Created by d.eroshenkov on 13.12.2018.
//

#pragma once

#include <vector>
#include <stdexcept>

template<class T>
class Deque
{
public:
    Deque()
    {
        front_.resize(0);
        back_.resize(0);
    }

    bool Empty() const
    {
        return front_.empty() && back_.empty();
    }

    size_t Size() const
    {
        return front_.size() + back_.size();
    }

    T &Front()
    {
        return front_.empty() ? back_.front() : front_.back();
    }

    const T &Front() const
    {
        return front_.empty() ? back_.front() : front_.back();
    }

    T &Back()
    {
        return back_.empty() ? front_.front() : back_.back();
    }

    const T &Back() const
    {
        return back_.empty() ? front_.front() : back_.back();
    }

    void PushFront(const T &value)
    {
        front_.push_back(value);
    }

    void PushBack(const T &value)
    {
        back_.push_back(value);
    }

    T &At(size_t index)
    {
        if (index >= Size())
        {
            throw std::out_of_range("");
        }

        if (index >= front_.size())
        {
            return back_[index - front_.size()];
        }
        else
        {
            return front_[front_.size() - index - 1];
        }
    }

    const T &At(size_t index) const
    {
        if (index >= Size())
        {
            throw std::out_of_range("");
        }

        if (index >= front_.size())
        {
            return back_[index - front_.size()];
        }
        else
        {
            return front_[front_.size() - index - 1];
        }
    }

    T &operator[](size_t index)
    {
        if (index >= front_.size())
        {
            return back_[index - front_.size()];
        }
        else
        {
            return front_[front_.size() - index - 1];
        }
    }

    const T &operator[](size_t index) const
    {
        if (index >= front_.size())
        {
            return back_[index - front_.size()];
        }
        else
        {
            return front_[front_.size() - index - 1];
        }
    }

private:
    std::vector<T> front_;
    std::vector<T> back_;
};