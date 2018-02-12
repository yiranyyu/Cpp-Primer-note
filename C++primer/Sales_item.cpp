#include "stdafx.h"
#include "Sales_item.h"
#include <stdexcept>
#include <iostream>
Sales_item::Sales_item(const std::string &_ID, int cnt, double price)
    :ID(_ID)
{
    if (cnt < 0 || price < 0)
        throw std::invalid_argument("negative cnt of price of Sales_item");
    this->copyCnt = cnt;
    this->averagePrice = price;
}

Sales_item::Sales_item()
    :ID(""),
    copyCnt(0),
    averagePrice(0) {}

Sales_item& Sales_item::operator=(const Sales_item &that)
{
    this->ID = that.ID;
    this->copyCnt = that.copyCnt;
    this->averagePrice = that.averagePrice;
    return *this;
}

Sales_item& Sales_item::operator+=(const Sales_item &that)
{
    if (this->ID != that.ID)
        throw std::invalid_argument("cannot add Sales_item of different ISBN");

    this->averagePrice = (this->copyCnt * this->averagePrice
        + that.copyCnt * that.averagePrice) / (this->copyCnt + that.copyCnt);
    this->copyCnt += that.copyCnt;
    return *this;
}


Sales_item Sales_item::operator+(const Sales_item &that)const
{
    return Sales_item(*this) += that;
}

Sales_item::~Sales_item()
{}

bool Sales_item::same_ISBN_with(const Sales_item &that)const noexcept
{
    return that.isbn() == that.isbn();
}

std::string Sales_item::isbn()const
{
    return this->ID;
}

std::ostream& operator<<(std::ostream &out, const Sales_item &item)
{
    out << item.ID << " " << item.copyCnt << " " << item.averagePrice;
    return out;
}
std::istream& operator>>(std::istream &in, Sales_item &item)
{
    in >> item.ID >> item.copyCnt >> item.averagePrice;
    return in;
}