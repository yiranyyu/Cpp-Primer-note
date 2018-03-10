#pragma once
#include "BulkQuote.h"
class BulkQuoteWithLimit :
    public BulkQuote
{
    using MyBase = BulkQuote;
public:
    BulkQuoteWithLimit();
    BulkQuoteWithLimit(const std::string &_bookNo, double price, std::size_t _min_pty,
                       double _discount, std::size_t _limit);
    virtual ~BulkQuoteWithLimit();

    virtual void debug() const noexcept override;
private:
    std::size_t limit;
};

