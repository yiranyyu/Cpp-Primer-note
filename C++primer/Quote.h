#pragma once
#include <string>
class Quote
{
public:
    Quote();
    Quote(const std::string &book, double salesPrice);
    virtual ~Quote();

    virtual double netPrice(std::size_t n)const;
    virtual void debug() const noexcept;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

