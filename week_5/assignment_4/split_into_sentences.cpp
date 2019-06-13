//
// Created by d.eroshenkov on 13.06.2019.
//

#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token> using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    // Напишите реализацию функции, не копируя объекты типа Token
}


struct TestToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }

    bool operator==(const TestToken &other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
    return stream << token.data;
}


struct NoncopyableToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }

    bool operator==(const NoncopyableToken &other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }

    NoncopyableToken(const NoncopyableToken &) = delete;
    NoncopyableToken &operator=(const NoncopyableToken &) = delete;

    NoncopyableToken(NoncopyableToken &&) = default;
    NoncopyableToken &operator=(NoncopyableToken &&) = default;
};

ostream &operator<<(ostream &stream, const NoncopyableToken &token)
{
    return stream << token.data;
}


// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"},
                                                       {"into"},
                                                       {"sentences"},
                                                       {"!"}})),
                 vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"},
                                                       {"into"},
                                                       {"sentences"},
                                                       {"!", true}})),
                 vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"},
                                                       {"into"},
                                                       {"sentences"},
                                                       {"!", true},
                                                       {"!", true},
                                                       {"Without"},
                                                       {"copies"},
                                                       {".", true}})), vector<Sentence<TestToken>>(
                         {
                             {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}}, {{"Without"}, {"copies"}, {".", true}},
                         }));
}

void TestSplittingNoncopy()
{
    vector<NoncopyableToken> item1, item2;
    item1.push_back({"Split"});
    item1.push_back({"into"});
    item1.push_back({"sentences"});
    item1.push_back({"!"});

    vector<Sentence<NoncopyableToken>> item3;
    item2.push_back({"Split"});
    item2.push_back({"into"});
    item2.push_back({"sentences"});
    item2.push_back({"!"});
    item3.push_back(move(item2));

    ASSERT_EQUAL(SplitIntoSentences(move(item1)), move(item3));

    item1.clear();
    item2.clear();
    item3.clear();

    item1.push_back({"Split"});
    item1.push_back({"into"});
    item1.push_back({"sentences"});
    item1.push_back({"!", true});

    item2.push_back({"Split"});
    item2.push_back({"into"});
    item2.push_back({"sentences"});
    item2.push_back({"!", true});

    item3.push_back(move(item2));

    ASSERT_EQUAL(SplitIntoSentences(move(item1)), move(item3));

    item1.clear();
    item2.clear();
    item3.clear();

    item1.push_back({"Split"});
    item1.push_back({"into"});
    item1.push_back({"sentences"});
    item1.push_back({"!", true});
    item1.push_back({"!", true});
    item1.push_back({"Without"});
    item1.push_back({"copies"});
    item1.push_back({".", true});

    item2.push_back({"Split"});
    item2.push_back({"into"});
    item2.push_back({"sentences"});
    item2.push_back({"!", true});
    item2.push_back({"!", true});
    item3.push_back(move(item2));

    item2.clear();

    item2.push_back({"Without"});
    item2.push_back({"copies"});
    item2.push_back({".", true});

    item3.push_back(move(item2));

    ASSERT_EQUAL(SplitIntoSentences(move(item1)), move(item3));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    RUN_TEST(tr, TestSplittingNoncopy);
    return 0;
}