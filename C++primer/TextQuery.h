#pragma once
#include <string>
#include <iosfwd>
#include <set>
#include <unordered_map>
#include "StrVec.h"
class QueryResult;
class TextQuery
{
    friend class QueryResult;
public:
    TextQuery(std::istream &in);
    ~TextQuery() = default;

    QueryResult query(const std::string &word) const;

private:
    void mapLine(const std::string &line);

private:
    std::shared_ptr<StrVec> pText;
    std::unordered_map<std::string, std::shared_ptr<std::set<size_t>>> wordMap;
};
void runTextQueries(std::istream &in);