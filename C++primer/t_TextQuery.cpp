//
// Created by yirany on 2018/4/4.
//
#include "t_TextQuery.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>

using namespace std;

t_TextQuery::t_TextQuery(std::istream &in)
        :pText(make_shared<StrVec>())
{
    string line;
    while (getline(in, line))
    {
        pText->push_back(line);
        mapLine(line);
    }
}

void t_TextQuery::mapLine(const std::string &line)
{
    static auto findRealWord = [](const string &word)->auto{

        size_t first = 0, last = string::npos;
        size_t i = 0;
        for (; i < word.size(); ++i)
            if (isalpha(word[i]))
            {
                first = i;
                break;
            }

        for (; i < word.size(); ++i)
            if (!isalpha(word[i]))
            {
                last = i;
                break;
            }
        return make_pair(first, last);
    };
    static size_t curLine = 0;

    stringstream in(line);
    string word;
    while (in >> word)
    {
        auto indices = findRealWord(word);
        string realWord = word.substr(indices.first, indices.second);
        for (auto &c : realWord)
            c = static_cast<char>(tolower(c));
        if (wordMap.find(realWord) == wordMap.end())
            wordMap[realWord] = make_shared<set<size_t>>();
        wordMap[realWord]->insert(curLine);
    }
    ++curLine;
}

t_TextQuery::QueryResult t_TextQuery::query(const std::string &word) const
{
    auto iter = wordMap.find(word);
    decltype(wordMap)::value_type::second_type lines;
    if (iter != wordMap.end())
        lines = iter->second;
    return {pText, lines, word};
}

std::ostream& operator<<(std::ostream &out, const t_TextQuery::QueryResult &result)
{
    if (!get<1>(result))
    {
        out << "not found";
        return out;
    }

    auto pText = get<0>(result);
    auto lines = get<1>(result);
    auto &word = get<2>(result);
    out << word << " occurs " << lines->size()
        << (lines->size() > 1 ? " times" : " time") << endl;
    for (const auto &index : *lines)
        cout << "  (line " << setw(6) << index << ") " << (*pText)[index] << endl;
    return out;
}

void run_t_TextQuery(std::istream &in)
{
    t_TextQuery tq(in);
    std::string q;
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        if (!(std::cin >> q) || q == "q")
            break;
        for (auto &c : q)
            c = static_cast<char>(tolower(c));
        std::cout << tq.query(q) << std::endl;
    }
}
