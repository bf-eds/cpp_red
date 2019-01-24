//
// Created by d.eroshenkov on 24.01.2019.
//

#include <string>
#include <list>
#include <algorithm>
#include "test_runner.h"
using namespace std;

class Editor
{
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() : position_(data_.end())
    {
    }

    void Left()   // сдвинуть курсор влево
    {
        if (position_ != data_.begin())
        {
            position_--;
        }
    }

    void Right()  // сдвинуть курсор вправо
    {
        if (position_ != data_.end())
        {
            position_++;
        }
    }

    void Insert(char token)   // вставить символ token
    {
        data_.insert(position_, token);
    }

    void Copy(size_t tokens)  // cкопировать  не более tokens символов,  начиная с текущей позиции курсора
    {
        if (tokens != 0)
        {
            tokens = min(tokens, static_cast<size_t>(distance(position_, data_.end())));
            buffer_ = {position_, next(position_, tokens)};
        }
        else
        {
            buffer_ = {};
        }
    }

    void Cut(size_t tokens)  // вырезать не более tokens символов,  начиная с текущей позиции курсора
    {
        Copy(tokens);
        tokens = min(tokens, static_cast<size_t>(distance(position_, data_.end())));
        position_ = data_.erase(position_, next(position_, tokens));
    }

    void Paste()  // вставить содержимое буфера в текущую позицию курсора
    {
        data_.insert(position_, buffer_.begin(), buffer_.end());
    }

    string GetText() const  // получить текущее содержимое  текстового редактора
    {
        return string(data_.begin(), data_.end());
    }

private:
    list<char> data_;
    list<char> buffer_;
    list<char>::iterator position_;
};

void TypeText(Editor &editor, const string &text)
{
    for (char c : text)
    {
        editor.Insert(c);
    }
}

void TestEditing()
{
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i)
        {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i)
        {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse()
{
    Editor editor;

    const string text = "esreveR";
    for (char c : text)
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}