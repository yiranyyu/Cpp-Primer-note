#include <stdexcept>
#include <iostream>
#include "Quote.h"
using namespace std;


Quote::Quote()
{
    cout << "Quote::Quote()" << endl;
}

Quote::Quote(const std::string & book, double salesPrice)
    :bookNo(book), price(salesPrice)
{
    if (price < 0.0)
        throw std::runtime_error("negative price (" + to_string(price) + ")");
}

Quote::Quote(const Quote &that)
    : bookNo(that.bookNo), price(that.price)
{
    cout << "Quote(const Quote&)" << endl;
}

Quote::Quote(Quote &&that)
    :bookNo(std::move(that.bookNo)), price(that.price)
{
    cout << "Quote(Quote &&)" << endl;
}

Quote& Quote::operator=(const Quote &that)
{
    this->bookNo = that.bookNo;
    this->price = that.price;
    cout << "Quote::operator=(const Quote&)" << endl;
    return *this;
}

Quote& Quote::operator=(Quote &&that)
{
    this->bookNo = std::move(that.bookNo);
    this->price = that.price;
    cout << "Quote::operator=(Quote&&)" << endl;
    return *this;
}

Quote::~Quote()
{
    cout << "Quote::~Quote()" << endl;
}

Quote * Quote::clone() const &
{
    return new Quote(*this);
}

Quote * Quote::clone() &&
{
    return new Quote(std::move(*this));
}

double Quote::netPrice(std::size_t n) const noexcept
{
    return n * price;
}

void Quote::debug() const noexcept
{
    cout << "bookNo: " << bookNo << ", " << "price: " << price;
}

const std::string & Quote::isbn() const noexcept
{
    return bookNo;
}

double print_total(std::ostream & os, const Quote & item, size_t n)
{
    double rtn = item.netPrice(n);
    os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << rtn << endl;
    return rtn;
}
