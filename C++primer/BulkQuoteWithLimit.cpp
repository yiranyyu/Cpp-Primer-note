#include <iostream>
#include "BulkQuoteWithLimit.h"
using namespace std;


BulkQuoteWithLimit::BulkQuoteWithLimit(const std::string & _bookNo, double price, std::size_t _min_pty,
                                       double _discount, std::size_t _limit)
    :MyBase(_bookNo, price, _min_pty, _discount), limit(_limit)
{}

BulkQuoteWithLimit * BulkQuoteWithLimit::clone() const &
{
    return new BulkQuoteWithLimit(*this);
}

BulkQuoteWithLimit * BulkQuoteWithLimit::clone() &&
{
    return new BulkQuoteWithLimit(std::move(*this));
}

void BulkQuoteWithLimit::debug() const noexcept
{
    MyBase::debug();
    cout << "amount limit: " << limit;
}
