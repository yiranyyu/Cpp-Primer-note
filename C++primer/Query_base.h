#pragma once
#include "QueryResult.h"
#include <string>
class Query_base
{
    friend class Query;
public:
    Query_base();
    virtual ~Query_base() = 0;
private:
    virtual QueryResult evaluate(const TextQuery &text)const = 0;
    virtual std::string represent()const = 0;
};

