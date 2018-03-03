#pragma once
#include <vector>
#include <string>
#include <iosfwd>
#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <unordered_map>
#include "StrVec.h"
class QueryResult;
class TextQuery
{
    friend class QueryResult;
public:
    TextQuery(std::istream &in);
    ~TextQuery() = default;

    QueryResult query(const std::string &word);

private:
    void mapLine(const std::string &line);

private:
    std::shared_ptr<StrVec> pText;
    std::unordered_map<std::string, std::shared_ptr<std::set<size_t>>> wordMap;
};
void runQueries(std::istream &in);