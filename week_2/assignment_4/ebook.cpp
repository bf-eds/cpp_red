//
// Created by human on 01.01.2019.
//

#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ReadingManager
{
public:
    ReadingManager() : user_page_(MAX_USER_COUNT_ + 1, 0), page_read_counts_(MAX_PAGE_COUNT_ + 1, 0), users_()
    {
    }

    void Read(int user_id, int page_count)
    {
        if (page_read_counts_[user_page_[user_id]] != 0)
        {
            page_read_counts_[user_page_[user_id]]--;
        }
        page_read_counts_[page_count]++;
        user_page_[user_id] = page_count;
        users_.insert(user_id);
    }

    double Cheer(int user_id) const
    {
        if (user_page_[user_id] == 0)
        {
            return 0;
        }

        if (users_.size() == 1)
        {
            return 1;
        }

        int pages = 0;
        for (int i = 1; i < user_page_.at(user_id); i++)
        {
            pages += page_read_counts_[i];
        }
        return pages * 1.0 / (users_.size() - 1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> user_page_;
    vector<int> page_read_counts_;
    set<int> users_;
};

int main()
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER")
        {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
