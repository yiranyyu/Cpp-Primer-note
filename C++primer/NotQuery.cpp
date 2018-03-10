#include <memory>
#include "NotQuery.h"
using namespace std;

NotQuery::NotQuery(const Query & q)
    :query(q)
{}

std::string NotQuery::represent() const
{
    return "~(" + query.represent() + ")";
}

QueryResult NotQuery::evaluate(const TextQuery & text) const
{
    auto result = query.evaluate(text);

    auto ret_lines = make_shared<set<QueryResult::line_type>>();

    auto cur = result.linesBegin(), end = result.linesEnd();

    auto size = result.getText()->size();
    for (QueryResult::line_type n = 0; n < size; ++n)
    {
        if (cur == end || *cur != n)
            ret_lines->insert(n); // if not in result add this line
        else if (cur != end)
            ++cur;
    }
    return QueryResult(result.getText(), ret_lines, represent());
}
