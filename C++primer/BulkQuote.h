#pragma once
#include "Quote.h"
class BulkQuote :
    public Quote
{
    using MyBase = Quote;
public:
    BulkQuote();
    virtual ~BulkQuote();
    BulkQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    virtual double netPrice(std::size_t amount) const override;
    virtual void debug() const noexcept override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

