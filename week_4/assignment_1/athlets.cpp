//
// Created by d.eroshenkov on 17.01.2019.
//

#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
    static int MAX_ATHLETS_NUMBER = 100000;

    int athlets_number = 0;
    cin >> athlets_number;

    list<int> athlets;
    vector<list<int>::iterator> postions(MAX_ATHLETS_NUMBER + 1, athlets.end());

    for (int i = 0; i < athlets_number; ++i)
    {
        int athlet_num = 0;
        int athlet_pos = 0;

        cin >> athlet_num >> athlet_pos;

        postions[athlet_num] = athlets.insert(postions[athlet_pos], athlet_num);;

    }

    for (int item : athlets)
    {
        cout << item << " ";
    }

    return 0;
}