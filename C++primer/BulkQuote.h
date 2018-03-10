#pragma once
#include "DiscountQuote.h"
class BulkQuote :
    public DiscountQuote
{
    using MyBase = DiscountQuote;
public:
    BulkQuote();
    BulkQuote(const std::string &_bookNo, double price, std::size_t _min_pty, double _discount);
    BulkQuote(const BulkQuote &that);
    BulkQuote(BulkQuote &&that);
    BulkQuote& operator=(const BulkQuote &that);
    BulkQuote& operator=(BulkQuote &&that);
    ~BulkQuote();
    virtual double netPrice(std::size_t amount) const noexcept override;
    virtual BulkQuote* clone() const & override;
    virtual BulkQuote* clone() && override;
};

