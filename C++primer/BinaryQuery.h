#pragma once
#include "Query_base.h"
#include "Query.h"
class BinaryQuery :
    public Query_base
{
protected:
    BinaryQuery(const Query &lhs, const Query &rhs, const std::string &op);
    virtual ~BinaryQuery();
    virtual std::string represent() const override;

    Query lhs;
    Query rhs;
    std::string op;
};

