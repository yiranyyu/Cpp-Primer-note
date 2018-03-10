#pragma once
#include "Quote.h"
class DiscountQuote :
    public Quote
{
    using MyBase = Quote;
public:
    DiscountQuote();
    DiscountQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    virtual ~DiscountQuote() = 0;

    virtual void debug()const noexcept override;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

