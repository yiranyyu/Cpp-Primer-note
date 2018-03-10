#include "WordQuery.h"
#include "TextQuery.h"


WordQuery::WordQuery(const std::string &word)
    :query_word(word)
{}

QueryResult WordQuery::evaluate(const TextQuery & text) const
{
    return text.query(query_word);
}

std::string WordQuery::represent() const
{
    return query_word;
}
