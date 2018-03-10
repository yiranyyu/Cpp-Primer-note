#pragma once
#include "DiscountQuote.h"
class BulkQuote :
    public DiscountQuote
{
    using MyBase = DiscountQuote;
public:
    BulkQuote();
    BulkQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    virtual ~BulkQuote();
    virtual double netPrice(std::size_t amount) const override;
};

