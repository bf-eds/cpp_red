#include "search_server.h"
#include "iterator_range.h"
//#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(const string &line)
{
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input)
{
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input)
{
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);)
    {
        new_index.Add(move(current_document));
    }

    index_ = move(new_index);
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output)
{
    vector<size_t> docid_count(index_.GetDocsCount());

    for (string current_query; getline(query_input, current_query);)
    {
        const auto words = SplitIntoWords(current_query);

        for (const auto &word : words)
        {
            for (const auto[docid, hintpoint] : index_.Lookup(word))
            {
                docid_count[docid] += hintpoint;
            }
        }

        vector<size_t> search_results(docid_count.size());
        iota(search_results.begin(), search_results.end(), 0);

        partial_sort(search_results.begin(), Head(search_results, 5).end(), end(search_results),
                     [&docid_count](const size_t &lhs, const size_t &rhs)
                     {
                         int64_t lhs_id = lhs;
                         int64_t rhs_id = rhs;
                         return make_pair(docid_count[lhs], -lhs_id) > make_pair(docid_count[rhs], -rhs_id);
                     });

        search_results_output << current_query << ':';
        for (auto docid : Head(search_results, 5))
        {
            if (docid_count[docid])
            {
                search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << docid_count[docid]
                                      << '}';
            }
        }
        search_results_output << endl;
        docid_count.assign(index_.GetDocsCount(), 0);
    }
}

void InvertedIndex::Add(const string &document)
{
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(document))
    {
        if (!index[word].empty())
        {
            if (index[word].back().first != docid)
            {
                index[word].push_back({docid, 1});
            }
            else
            {
                index[word].back().second++;
            }
        }
        else
        {
            index[word].push_back({docid, 1});
        }
    }
}

const vector<pair<size_t, size_t>> &InvertedIndex::Lookup(const string &word) const
{
    if (auto it = index.find(word); it != index.end())
    {
        return it->second;
    }
    else
    {
        return not_found;
    }
}
