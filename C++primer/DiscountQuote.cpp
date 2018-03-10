#include <stdexcept>
#include <iostream>
#include "DiscountQuote.h"
using namespace std;


DiscountQuote::DiscountQuote()
{
    cout << "DicountQuote::DiscountQuote()" << endl;
}

DiscountQuote::DiscountQuote(const std::string & _bookNo, double price, std::size_t _min_qty, double _discount)
    :Quote(_bookNo, price), quantity(_min_qty), discount(_discount)
{
    if (discount < 0.0 || discount > 1.0)
        throw runtime_error("discount must be in range [0.0, 1.0] but found discount = " + to_string(discount));
}

DiscountQuote::DiscountQuote(const DiscountQuote & that)
    :MyBase(that), quantity(that.quantity), discount(that.discount)
{
    cout << "DiscountQuote::DiscountQuote(const DiscountQuote &)" << endl;
}

DiscountQuote::DiscountQuote(DiscountQuote && that)
    :MyBase(std::move(that)), quantity(that.quantity), discount(that.discount)
{
    cout << "DiscountQuote::DiscountQuote(DiscountQuote &&)" << endl;
}

DiscountQuote & DiscountQuote::operator=(const DiscountQuote & that)
{
    MyBase::operator=(that);
    this->quantity = that.quantity;
    this->discount = that.discount;
    cout << "DiscountQuote & DiscountQuote::operator=(const DiscountQuote&)" << endl;
    return *this;
}

DiscountQuote & DiscountQuote::operator=(DiscountQuote && that)
{
    MyBase::operator=(std::move(that));
    this->quantity = that.quantity;
    this->discount = that.discount;
    cout << "DiscountQuote & DiscountQuote::operator=(const DiscountQuote &)" << endl;
    return *this;
}

DiscountQuote::~DiscountQuote()
{
    cout << "DiscountQuote::~DiscountQuote()" << endl;
}

void DiscountQuote::debug()const noexcept
{
    MyBase::debug();
    cout << "min quantity: " << quantity << " discount: " << discount;
}
