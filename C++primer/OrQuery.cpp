#include "OrQuery.h"
#include <algorithm>
#include <iterator>
using namespace std;

OrQuery::OrQuery(const Query & left, const Query & right)
    :MyBase(left, right, "|")
{}

QueryResult OrQuery::evaluate(const TextQuery & text) const
{
    auto left = lhs.evaluate(text), right = rhs.evaluate(text);

    auto ret_lines = make_shared<set<QueryResult::line_type>>(left.linesBegin(), left.linesEnd());

    ret_lines->insert(right.linesBegin(), right.linesEnd());
    return QueryResult(left.getText(), ret_lines, represent());
}
