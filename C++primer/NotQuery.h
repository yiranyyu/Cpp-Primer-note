#pragma once
#include <memory>
#include "Query_base.h"
#include "Query.h"
class NotQuery :
    public Query_base
{
    friend Query Query::operator~()const;
private:
    NotQuery(const Query &q);
    virtual std::string represent() const override;
    virtual QueryResult evaluate(const TextQuery &text) const override;

    Query query;
};