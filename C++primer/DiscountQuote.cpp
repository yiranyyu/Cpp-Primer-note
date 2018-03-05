#include <stdexcept>
#include "DiscountQuote.h"
using namespace std;


DiscountQuote::DiscountQuote() = default;

DiscountQuote::DiscountQuote(const std::string & _bookNo, double price, std::size_t _min_qty, double _discount)
    :Quote(_bookNo, price), quantity(_min_qty), discount(_discount)
{
    if (discount < 0.0 || discount > 1.0)
        throw runtime_error("discount must be in range [0.0, 1.0] but found discount = " + to_string(discount));
}


DiscountQuote::~DiscountQuote() = default;