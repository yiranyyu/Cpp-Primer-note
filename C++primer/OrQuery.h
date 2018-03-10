#pragma once
#include "BinaryQuery.h"
class OrQuery :
    public BinaryQuery
{
    friend Query Query::operator|(const Query&)const;
private:
    using MyBase = BinaryQuery;
    OrQuery(const Query &left, const Query &right);
    virtual QueryResult evaluate(const TextQuery &text) const override;
};

