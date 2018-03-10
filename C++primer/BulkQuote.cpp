#include <stdexcept>
#include <iostream>
#include "BulkQuote.h"
using namespace std;

BulkQuote::BulkQuote() = default;

BulkQuote::BulkQuote(const std::string & _bookNo, double price, std::size_t _min_qty, double _discount)
    :MyBase(_bookNo, price)
{}

double BulkQuote::netPrice(std::size_t amount) const
{
    if (amount > quantity)
        return amount * (1 - discount) * price;
    return amount * price;
}

BulkQuote::~BulkQuote() = default;