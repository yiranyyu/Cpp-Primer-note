#pragma once
#include <set>
#include <memory>
#include "Quote.h"
class Basket
{
public:
    void addItem(const Quote &item);
    void addItem(Quote &&item);
    double total_receipt(std::ostream &os)const;
private:
    static bool cmp(const std::shared_ptr<Quote> a, const std::shared_ptr<Quote> b)
    {
        return a->isbn() < b->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(cmp)*> items;
};

