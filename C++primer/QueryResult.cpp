#include "QueryResult.h"
#include <iostream>
#include <iomanip>
#include "TextQuery.h"
using namespace std;


QueryResult::QueryResult(const TextQuery &content, const std::string &_word)
    :pText(content.pText), word(_word)
{
    auto iter = content.wordMap.find(word);
    if (iter != content.wordMap.end())
        lines = iter->second;
}

std::ostream &operator<<(std::ostream &out, const QueryResult &result)
{
    if (!result.lines)
    {
        out << "not found";
        return out;
    }
    out << result.word << " occurs " << result.lines->size()
        << (result.lines->size() > 1 ? " times" : " time") << endl;
    for (const auto &index : *result.lines)
        cout << "  (line " << setw(6) << index << ") " << (*result.pText)[index] << endl;
    return out;
}

QueryResult::line_iter QueryResult::linesBegin() const
{
    return lines->cbegin();
}

QueryResult::line_iter QueryResult::linesEnd() const
{
    return lines->cend();
}

QueryResult::QueryResult(const shared_ptr<QueryResult::text_type> &_pText,
                         const shared_ptr<set<QueryResult::line_type>> &_lines, const std::string &represent)
    :pText(_pText), lines(_lines), word(represent)
{}
