#include "TextQuery.h"
#include <iostream>
#include <sstream>
#include "QueryResult.h"
using namespace std;

TextQuery::TextQuery(std::istream &in)
    :pText(make_shared<StrVec>())
{
    string line;
    while (getline(in, line))
    {
        pText->push_back(line);
        mapLine(line);
    }
}

void TextQuery::mapLine(const std::string &line) 
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

QueryResult TextQuery::query(const std::string &word)
{
    return QueryResult(*this, word);
}

void runQueries(std::istream &in)
{
    TextQuery tq(in);
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