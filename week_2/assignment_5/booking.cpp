//
// Created by human on 05.01.2019.
//

#include <iostream>
#include <map>
#include <queue>

//#include "test_runner.h"

using namespace std;

class BookingManager
{
public:
    BookingManager() : client_books_(), hotel_rooms_(), hotel_clients_()
    {
    }

    void Book(const int64_t time, const string &hotel_name, int client_id, int room_count)
    {
        client_books_.push({time, hotel_name, client_id, room_count});
        hotel_rooms_[hotel_name] += room_count;
        hotel_clients_[hotel_name][client_id]++;

        // Adjust
        while (!client_books_.empty() && (client_books_.front().time <= time - 86400))
        {
            string hotel = client_books_.front().hotel_name;
            int client = client_books_.front().client_id;
            hotel_rooms_[hotel] -= client_books_.front().room_count;

            if (hotel_rooms_[hotel] == 0)
            {
                hotel_rooms_.erase(hotel);
            }

            hotel_clients_[hotel][client]--;

            if (hotel_clients_[hotel][client] == 0)
            {
                hotel_clients_[hotel].erase(client);
            }

            client_books_.pop();
        }
    }

    int Clients(const string &hotel_name) const
    {
        return hotel_clients_.count(hotel_name) == 0 ? 0 : hotel_clients_.at(hotel_name).size();
    }

    int Rooms(const string &hotel_name) const
    {
        return hotel_rooms_.count(hotel_name) == 0 ? 0 : hotel_rooms_.at(hotel_name);
    }

private:

    struct event
    {
        int64_t time;
        string hotel_name;
        int client_id;
        int room_count;
    };

    queue<event> client_books_;
    map<string, int> hotel_rooms_; // ROOMS request.
    map<string, map<int, int>> hotel_clients_; // CLIENTS request.
};

/*
void test()
{
    BookingManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 4);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 1);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);

    manager.Book(999999999999999000, "hilton", 3, 5);
    manager.Book(999999999999999900, "hilton", 4, 3);
    manager.Book(999999999999999990, "mariot", 6, 1);
    manager.Book(999999999999999999, "mariot", 6, 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 8);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("mariot"), 3);
    ASSERT_EQUAL(manager.Clients("mariot"), 1);
}*/

int main()
{
//    TestRunner tr;
//    tr.RunTest(test, "test");


    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;

    int query_count = 0;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK")
        {
            int64_t time = 0;
            string hotel_name;
            int client_id = 0;
            int room_count = 0;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS")
        {
            string hotel_name;
            cin >> hotel_name;

            cout << manager.Clients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;

            cout << manager.Rooms(hotel_name) << endl;
        }
    }

    return 0;
}