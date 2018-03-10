#include "BinaryQuery.h"

BinaryQuery::BinaryQuery(const Query & _lhs, const Query & _rhs, const std::string &_op)
    :lhs(_lhs), rhs(_rhs), op(_op)
{}

BinaryQuery::~BinaryQuery()
{
}

std::string BinaryQuery::represent() const
{
    return "(" + lhs.represent() + " " + op + " " + rhs.represent() + ")";
}
