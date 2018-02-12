#include "stdafx.h"
#include "Sales_data.h"
#include <exception>
using namespace std;

Sales_data::Sales_data() = default;

Sales_data::Sales_data(const std::string &_bookNo)
    :bookNo(_bookNo)
{
    checkData();
}

Sales_data::Sales_data(const std::string &_bookNo, unsigned _sold_number, double price)
    :bookNo(_bookNo), sold_number(_sold_number), revenue(_sold_number * price)
{
    checkData();
}

Sales_data::Sales_data(const Sales_data& that)
    :bookNo(that.bookNo), sold_number(that.sold_number), revenue(that.revenue)
{
    checkData();
}

Sales_data::Sales_data(std::istream& in)
{
    read(in, *this);
    checkData();
}

Sales_data& Sales_data::combine(const Sales_data & that)
{
    if (this->bookNo != that.bookNo) 
        throw invalid_argument("cannot combine Sales_data of different ISBN one is " + isbn() + " one is " + that.isbn());

    this->sold_number += that.sold_number;
    this->revenue += that.revenue;
    return *this;
}

double Sales_data::avg_price() const noexcept
{
    if (sold_number == 0) return 0;
    return revenue / sold_number;
}

Sales_data add(const Sales_data & lhs, const Sales_data & rhs)
{
    Sales_data temp = lhs;
    return temp.combine(rhs);
}

std::ostream & print(std::ostream & out, const Sales_data & data)
{
    out << data.isbn() << ' ' << data.getSoldNumber() << ' '
        << data.getRevenue() << ' ' << data.avg_price();
    return out;
}

std::istream & read(std::istream & in, Sales_data & data)
{
    double price = 0.0;
    in >> data.bookNo >> data.sold_number >> price;
    data.revenue = data.sold_number * price;
    return in;
}


void Sales_data::checkData()
{
    if (sold_number < 0) throw invalid_argument("cannot init Sales_data obj with negative solds");
    if (bookNo.empty()) throw invalid_argument("cannot init Sales_data with empty ISBN");
}
