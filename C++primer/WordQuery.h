#pragma once
#include "Query_base.h"
class WordQuery :
    public Query_base
{
    friend class Query; // Query uses the WordQuery ctor
private:
    WordQuery(const std::string &word);

    virtual QueryResult evaluate(const TextQuery &text) const override;
    virtual std::string represent() const override;
    std::string query_word;
};

