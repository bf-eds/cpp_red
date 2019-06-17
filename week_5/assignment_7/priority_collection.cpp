//
// Created by d.eroshenkov on 17.06.2019.
//

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class PriorityCollection
{
public:
    using Id = int; /* тип, используемый для идентификаторов */

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        const auto size = objects_.size();
        objects_.push_back({move(object)});
        priorities_.insert({0, size});

        return size;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
    {
        while (range_begin != range_end)
        {
            *ids_begin++ = Add(move(*range_begin++));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        return id >= 0 && id < static_cast<int>(objects_.size()) && objects_[id].priority_ != NOT_EXIST;
    }

    // Получить объект по идентификатору
    const T &Get(Id id) const
    {
        return objects_[id].data_;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        priorities_.erase({objects_[id].priority_, id});
        objects_[id].priority_++;
        priorities_.insert({objects_[id].priority_, id});
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const
    {
        const auto &item = objects_[prev(priorities_.end())->second];
        return {item.data_, item.priority_};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        auto last = prev(priorities_.end());
        objects_[last->second].priority_ = NOT_EXIST;
        pair<T, int> tmp = {move(objects_[last->second].data_), last->first};
        priorities_.erase(last);

        return move(tmp);
    }

private:

    struct Object
    {
        T data_;
        int priority_ = 0;
    };

    static const int NOT_EXIST = -1;

    set<pair<int, Id>> priorities_;
    vector<Object> objects_;
};

class StringNonCopyable : public string
{
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}