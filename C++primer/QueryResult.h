#pragma once
#include <memory>
#include <set>
#include <iostream>
#include <vector>
#include "StrVec.h"
class TextQuery;
class QueryResult
{
    friend std::ostream& operator<<(std::ostream &out, const QueryResult &result);
private:
    using text_type = StrVec;
public:
    QueryResult(const TextQuery &content, const std::string &_word);

private:
    std::shared_ptr<text_type> pText;
    std::shared_ptr<std::set<size_t>> lines;
    std::string word;
};

