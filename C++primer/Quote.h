#pragma once
#include <string>
class Quote
{
public:
    Quote();
    Quote(const std::string &book, double salesPrice);
    Quote(const Quote&);
    Quote(Quote&&);
    Quote& operator=(const Quote&);
    Quote& operator=(Quote&&);
    virtual ~Quote();

    virtual Quote* clone() const &;
    virtual Quote* clone() && ;

    virtual double netPrice(std::size_t n)const noexcept;
    virtual void debug() const noexcept;
    const std::string& isbn()const noexcept;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

double print_total(std::ostream &os, const Quote &item, size_t n);
