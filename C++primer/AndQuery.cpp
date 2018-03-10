#include <memory>
#include <algorithm>
#include <iterator>
#include "AndQuery.h"
#include "QueryResult.h"
using namespace std;

AndQuery::AndQuery(const Query &left, const Query &right)
    :MyBase(left, right, "&")
{}

QueryResult AndQuery::evaluate(const TextQuery & text) const
{
    auto left = lhs.evaluate(text), right = rhs.evaluate(text);

    auto ret_lines = make_shared<set<QueryResult::line_type>>();
    set_intersection(left.linesBegin(), left.linesEnd(),
        right.linesBegin(), right.linesEnd(),
        inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(left.getText(), ret_lines, represent());
}