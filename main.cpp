#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class Human
{
public:
    Human(const string &name, const string &type) : Name(name), Type(type)
    {
    }

    void Log() const
    {
        cout << Type << ": ";
    }

    virtual void Walk(const string &destination) const = 0;
public:
    string Name;
    string Type;
};


class Student : public Human
{
public:

    Student(const string &name, const string &favouriteSong) : Human(name, "Student"), FavouriteSong(favouriteSong)
    {
    }

    void Learn() const
    {
        Log();
        cout << Name << " learns" << endl;
    }

    void SingSong() const
    {
        Log();
        cout << Name << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string &destination) const
    {
        Log();
        cout << Name << " walks to: " << destination << endl;
        SingSong();
    }

private:
    string FavouriteSong;
};


class Teacher : public Human
{
public:

    Teacher(const string &name, const string &subject) : Human(name, "Teacher"), Subject(subject)
    {
    }

    void Walk(const string &destination) const
    {
        Log();
        cout << Name << " walks to: " << destination << endl;
    }

    void Teach() const
    {
        Log();
        cout << Name << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman : public Human
{
public:
    Policeman(const string &name) : Human(name, "Policeman")
    {
    }

    void Walk(const string &destination) const
    {
        Log();
        cout << Name << " walks to: " << destination << endl;
    }

    void Check(const Human &t) const
    {
        Log();
        cout << Name << " checks " << t.Type << ". " << t.Type << "'s name is: " << t.Name << endl;
    }
};


void VisitPlaces(Human &t, const vector<string> &places)
{
    for (auto p : places)
    {
        t.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}


/*
Teacher: Jim walks to: Moscow
Teacher: Jim walks to: London
Policeman: Bob checks Student. Student's name is: Ann
Student: Ann walks to: Moscow
Student: Ann sings a song: We will rock you
Student: Ann walks to: London
Student: Ann sings a song: We will rock you
 */