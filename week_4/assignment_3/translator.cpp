//
// Created by human on 20.01.2019.
//

#include "test_runner.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Translator
{
public:
    void Add(string_view source, string_view target)
    {
        const auto source_view = GetStringView(source);
        const auto target_view = GetStringView(target);

        forward_[source_view] = target_view;
        backward_[target_view] = source_view;
    }

    string_view GetStringView(string_view str)
    {
        for (const auto &dict : {&forward_, &backward_})
        {
            const auto item = dict->find(str);
            if (item != dict->end())
            {
                return item->first;
            }
        }

        return strings_.emplace_back(str);
    }

    string_view Translate(const map<string_view, string_view> &dict, string_view word) const
    {
        if (const auto item = dict.find(word); item != dict.end())
        {
            return item->second;
        }
        else
        {
            return {};
        }
    }

    string_view TranslateForward(string_view source) const
    {
        return Translate(forward_, source);
    }

    string_view TranslateBackward(string_view target) const
    {
        return Translate(backward_, target);
    }

private:
    map<string_view, string_view> forward_;
    map<string_view, string_view> backward_;
    deque<string> strings_;
};

void TestSimple()
{
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}