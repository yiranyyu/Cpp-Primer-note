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
public:
    using text_type = StrVec;
    using line_type = size_t;
    using line_iter = std::set<line_type>::const_iterator;

public:
    QueryResult(const TextQuery &content, const std::string &_word);
    QueryResult(const std::shared_ptr<text_type> &_pText, const std::shared_ptr<std::set<line_type>> &lines, const std::string &represent);
    const std::shared_ptr<text_type>& getText()const noexcept;
    line_iter linesBegin() const;
    line_iter linesEnd() const;
private:
    std::shared_ptr<text_type> pText;
    std::shared_ptr<std::set<line_type>> lines;
    std::string word;
};

inline const std::shared_ptr<QueryResult::text_type>& QueryResult::getText() const noexcept
{
    return pText;
}
