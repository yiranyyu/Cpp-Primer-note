#include <string>
#include <memory>
#include <stdexcept>
#include "Query.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"
#include "WordQuery.h"
using namespace std;

Query::Query(const std::string &word)
    :impl(new WordQuery(word))
{}

Query Query::operator&(const Query & that) const
{
    return shared_ptr<Query_base>(new AndQuery(*this, that));
}

Query Query::operator|(const Query & that) const
{
    return shared_ptr<Query_base>(new OrQuery(*this, that));
}

Query Query::operator~() const
{
    return shared_ptr<Query_base>(new NotQuery(*this));
}

QueryResult Query::evaluate(const TextQuery &txt) const
{
    return impl->evaluate(txt);
}

std::string Query::represent() const
{
    return impl->represent();
}

Query::Query(std::shared_ptr<Query_base> query)
    :impl(query)
{}

Query::Query() = default;

std::ostream& operator<<(std::ostream &os, const Query &query)
{
    os << query.represent();
    return os;
}
