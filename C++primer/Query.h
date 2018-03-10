#pragma once
#include <string>
#include <memory>
#include "Query_base.h"
#include "TextQuery.h"
class Query
{
public:
    Query(const std::string & word);

    Query operator& (const Query &that) const;
    Query operator| (const Query &that) const;
    Query operator~ () const;

    QueryResult evaluate(const TextQuery &txt) const;
    std::string represent()const;
private:
    Query(std::shared_ptr<Query_base> query);
    Query();
    std::shared_ptr<Query_base> impl;
};

std::ostream& operator<<(std::ostream &os, const Query &query);
