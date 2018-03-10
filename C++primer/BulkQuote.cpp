#include <stdexcept>
#include <iostream>
#include "BulkQuote.h"
using namespace std;

BulkQuote::BulkQuote()
    :MyBase()
{
    cout << "BulkQuote::BulkQuote()" << endl;
}

BulkQuote::BulkQuote(const std::string & _bookNo, double price, std::size_t _min_qty, double _discount)
    :MyBase(_bookNo, price, _min_qty, _discount)
{}

BulkQuote::BulkQuote(const BulkQuote & that)
    :MyBase(that)
{
    cout << "BulkQuote::BulkQuote(const BulkQuote &)" << endl;
}

BulkQuote::BulkQuote(BulkQuote && that)
    :MyBase(std::move(that))
{
    cout << "BulkQuote::BulkQuote(BulkQuote && )" << endl;
}

BulkQuote & BulkQuote::operator=(const BulkQuote & that)
{
    MyBase::operator=(that);
    cout << "BulkQuote & BulkQuote::operator=(const BulkQuote &)" << endl;
    return *this;
}

BulkQuote & BulkQuote::operator=(BulkQuote && that)
{
    MyBase::operator=(std::move(that));
    cout << "BulkQuote & BulkQuote::operator=(const BulkQuote &&)" << endl;
    return *this;
}

BulkQuote::~BulkQuote()
{
    cout << "BulkQuote::~BulkQuote()" << endl;
}

BulkQuote * BulkQuote::clone() const &
{
    return new BulkQuote(*this);
}

BulkQuote * BulkQuote::clone() &&
{
    return new BulkQuote(std::move(*this));
}

double BulkQuote::netPrice(std::size_t amount) const noexcept
{
    if (amount > quantity)
        return amount * (1 - discount) * price;
    return amount * price;
}
