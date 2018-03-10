#pragma once
#include "Quote.h"
class DiscountQuote :
    public Quote
{
    using MyBase = Quote;
public:
    DiscountQuote();
    DiscountQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    DiscountQuote(const DiscountQuote &that);
    DiscountQuote(DiscountQuote &&that);
    DiscountQuote& operator=(const DiscountQuote &that);
    DiscountQuote& operator=(DiscountQuote &&that);
    virtual ~DiscountQuote() = 0;

    virtual void debug()const noexcept override;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

