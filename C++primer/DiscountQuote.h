#pragma once
#include "Quote.h"
class DiscountQuote :
    public Quote
{
public:
    DiscountQuote();
    DiscountQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    virtual ~DiscountQuote();
private:
    std::size_t quantity = 0;
    double discount = 0.0;
};

