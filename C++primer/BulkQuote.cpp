#include <stdexcept>
#include <string>
#include <iostream>
#include "BulkQuote.h"
using namespace std;

BulkQuote::BulkQuote() = default;

BulkQuote::BulkQuote(const std::string & _bookNo, double price, std::size_t _min_qty, double _discount)
    :Quote(_bookNo, price), min_qty(_min_qty), discount(_discount)
{
    if (discount < 0.0 || discount > 1.0)
        throw runtime_error("discount must be in range [0.0, 1.0] but found discount = " + to_string(discount));
}

double BulkQuote::netPrice(std::size_t amount) const
{
    if (amount > min_qty)
        return amount * (1 - discount) * price;
    return amount * price;
}

void BulkQuote::debug() const noexcept
{
    MyBase::debug();
    cout << "minist quantity: " << min_qty << ", " << "discount: " << discount;
}


BulkQuote::~BulkQuote() = default;