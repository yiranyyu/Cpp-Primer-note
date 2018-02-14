#pragma once
#include <string>
class Sales_data
{
    friend std::istream& read(std::istream &in, Sales_data &data);
public:
    Sales_data();
    explicit Sales_data(const std::string &_bookNo);
    explicit Sales_data(std::istream& in);
    Sales_data(const std::string &_bookNo, unsigned _units_sold, double price);
    Sales_data(const Sales_data& that);

    void checkData();

    Sales_data& combine(const Sales_data &that);

    double avg_price() const noexcept
    {
        if (sold_number == 0) return 0;
        return revenue / sold_number;
    }

    std::string isbn() const noexcept
    {
        return bookNo; 
    }

    unsigned getSoldNumber() const noexcept
    {
        return sold_number; 
    }

    double getRevenue() const noexcept
    {
        return revenue; 
    }

private:
    std::string bookNo;
    unsigned sold_number = 0;
    double revenue = 0.0;
};

std::istream& read(std::istream &in, Sales_data & data);
Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
std::ostream& print(std::ostream &out, const Sales_data &data);