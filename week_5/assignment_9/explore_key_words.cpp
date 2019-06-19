//
// Created by d.eroshenkov on 19.06.2019.
//

#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <future>
using namespace std;

template<typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end) : first(begin), last(end), size_(distance(first, last))
    {
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template<typename Iterator>
class Paginator
{
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    {
        for (size_t left = distance(begin, end); left > 0;)
        {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const
    {
        return pages.begin();
    }

    auto end() const
    {
        return pages.end();
    }

    size_t size() const
    {
        return pages.size();
    }
};

template<typename C>
auto Paginate(C &c, size_t page_size)
{
    return Paginator(begin(c), end(c), page_size);
}

struct Stats
{
    map<string, int> word_frequences;

    void operator+=(const Stats &other)
    {
        for (const auto &word : other.word_frequences)
        {
            word_frequences[word.first]++;
        }
    }
};

Stats ExploreLine(const set<string> &key_words, const string &line)
{
    stringstream ss(line);
    string str;
    Stats stats;

    while (ss >> str)
    {
        if (key_words.count(str))
        {
            stats.word_frequences[str]++;
        }
    }

    return stats;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input)
{
    Stats result;
    for (string line; getline(input, line);)
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
    vector<future<Stats>> futures;
    Stats stats;
    string line;

    while (getline(input, line))
    {
        stringstream ss;
        ss << line;
//        for (int i = 1; i < 1000 && getline(input, line); ++i)
//        {
//            ss << line << " ";
//        }

        cout << "ss: " << ss.str() << endl;

//        ss << "asdf asdfa sdf asdf as df";

        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(ss)));
    }

    for (auto &f : futures)
    {
        stats += f.get();
    }

    return stats;
}

void TestBasic()
{
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {{"yangle", 6},
                                       {"rocks",  2},
                                       {"sucks",  1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}