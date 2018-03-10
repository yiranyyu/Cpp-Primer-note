#include "Basket.h"
#include <iostream>
using namespace std;

void Basket::addItem(const Quote & item)
{
    items.insert(std::shared_ptr<Quote>(item.clone()));
}

void Basket::addItem(Quote && item)
{
    items.insert(std::shared_ptr<Quote>(std::move(item).clone()));
}

double Basket::total_receipt(std::ostream & os) const
{
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
    {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << endl;
    return sum;
}
