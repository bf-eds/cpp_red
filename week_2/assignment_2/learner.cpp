//
// Created by human on 30.12.2018.
//

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner
{
private:
    set<string> dict;
public:
    int Learn(const vector<string> &words)
    {
        int oldSize = dict.size();
        dict.insert(words.begin(), words.end());
        return dict.size() - oldSize;
    }

    vector<string> KnownWords()
    {
        return {dict.begin(), dict.end()};
    }
};