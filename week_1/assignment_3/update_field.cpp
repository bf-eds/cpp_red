//
// Created by human on 09.12.2018.
//

#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

istream &operator>>(istream &is, Date &date)
{
    int year = 0;
    int month = 0;
    int day = 0;

    is >> year;
    if (is.peek() != '-')
    {
        date = {};
    }
    is.ignore(1);

    is >> month;
    if (is.peek() != '-')
    {
        date = {};
    }
    is.ignore(1);

    is >> day;
    if ((is.peek() != ' ') && !is.eof())
    {
        date = {};
    }

    date = {year, month, day};

    return is;
}

istream &operator>>(istream &is, Time &time)
{
    int hours = 0;
    int minutes = 0;

    is >> hours;
    if (is.peek() != ':')
    {
        time = {};
    }
    is.ignore(1);

    is >> minutes;

    time = {hours, minutes};

    return is;
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return vector<int>{lhs.year, lhs.month, lhs.day} == vector<int>{rhs.year, rhs.month, rhs.day};
}

ostream &operator<<(ostream &os, const Date &date)
{
    return os << date.year << "-" << date.month << " " << date.day << endl;
}

bool operator==(const Time &lhs, const Time &rhs)
{
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream &operator<<(ostream &os, const Time &time)
{
    return os << time.hours << ":" << time.minutes << endl;
}

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time
#define UPDATE_FIELD(ticket, field, values) \
    {                                       \
        auto it = (values).find(#field);    \
        if (it != (values).end())           \
        {                                   \
            istringstream is(it->second);   \
            is >> (ticket).field;           \
        }                                   \
    }                                       \


void TestUpdate()
{
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {{"departure_date", "2018-2-28"},
                                          {"departure_time", "17:40"},};
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {{"price",        "12550"},
                                          {"arrival_time", "20:33"},};
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}