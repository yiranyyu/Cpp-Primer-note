#include <iostream>
#include "BulkQuoteWithLimit.h"
using namespace std;


BulkQuoteWithLimit::BulkQuoteWithLimit() = default;

BulkQuoteWithLimit::BulkQuoteWithLimit(
    const std::string & _bookNo, double price, std::size_t _min_pty, 
    double _discount, std::size_t _limit
)
    :BulkQuote(_bookNo, price, _min_pty, _discount), limit(_limit)
{
}


BulkQuoteWithLimit::~BulkQuoteWithLimit() = default;

void BulkQuoteWithLimit::debug() const noexcept
{
    MyBase::debug();
    cout << "amout limit: " << limit;
}
