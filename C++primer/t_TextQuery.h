//
// Created by yirany on 2018/4/4.
//

#ifndef C_PRIMER_T_TEXTQUERY_H
#define C_PRIMER_T_TEXTQUERY_H

#include <iosfwd>
#include "StrVec.h"
#include <set>
#include <unordered_map>
#include <tuple>

class t_TextQuery
{
public:
    using QueryResult = std::tuple<std::shared_ptr<StrVec>,
                                   std::shared_ptr<std::set<size_t>>,
                                   std::string>;
    friend std::ostream& operator<<(std::ostream &os, const QueryResult &result);
public:
    t_TextQuery(std::istream &in);
    ~t_TextQuery() = default;

    QueryResult query(const std::string &word) const;

private:
    void mapLine(const std::string &line);

private:
    std::shared_ptr<StrVec> pText;
    std::unordered_map<std::string, std::shared_ptr<std::set<size_t>>> wordMap;
};

std::ostream& operator<<(std::ostream &out, const t_TextQuery::QueryResult &result);
void run_t_TextQuery(std::istream &in);

#endif //C_PRIMER_T_TEXTQUERY_H
