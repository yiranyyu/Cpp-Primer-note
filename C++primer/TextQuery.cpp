#include "TextQuery.h"
#include <iostream>
#include <sstream>
#include "QueryResult.h"
using namespace std;

TextQuery::TextQuery(std::istream &in)
    :pText(make_shared<vector<string>>())
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
    static auto findPunc = [](const string &word)->auto{
        for (size_t i = 0; i < word.size(); ++i)
            if (ispunct(word[i]))
                return i;
        return word.size();
    };
    static size_t curLine = 0;

    stringstream in(line);
    string word;
    while (in >> word)
    {
        string realWord = word.substr(0, findPunc(word));
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
        std::cout << tq.query(q) << std::endl;
    }
}