#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <unordered_map>

using namespace std;

template<typename T>
class Synchronized
{
public:
    explicit Synchronized(T initial = T()) : value(move(initial))
    {
    }

    struct Access
    {
        lock_guard<mutex> guard;
        T &ref_to_value;
    };

    Access GetAccess()
    {
        return {lock_guard(m), value};
    }

private:
    mutex m;
    T value;
};

class InvertedIndex
{
public:
    void Add(const string &document);
    const vector<pair<size_t, size_t>> &Lookup(const string &word) const;

    const string &GetDocument(size_t id) const
    {
        return docs[id];
    }

    size_t GetDocsCount() const
    {
        return docs.size();
    }

private:
    unordered_map<string, vector<pair<size_t, size_t>>> index;
    vector<string> docs;
    vector<pair<size_t, size_t>> not_found;
};

class SearchServer
{
public:
    SearchServer() = default;
    explicit SearchServer(istream &document_input);
    void UpdateDocumentBase(istream &document_input);
    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    InvertedIndex index_;
};
