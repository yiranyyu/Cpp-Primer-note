#include <stdexcept>
#include <iostream>
#include "Quote.h"
using namespace std;


Quote::Quote() = default;

Quote::Quote(const std::string & book, double salesPrice)
    :bookNo(book), price(salesPrice)
{
    if (price < 0.0)
        throw std::runtime_error("negative price (" + to_string(price) + ")");
}


Quote::~Quote() = default;

double Quote::netPrice(std::size_t n) const noexcept
{
    return n * price;
}

void Quote::debug() const noexcept
{
    cout << "bookNo: " << bookNo << ", " << "price: " << price;
}
