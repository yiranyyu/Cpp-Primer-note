#pragma once
#include <string>
#include <iosfwd>
class Sales_item
{
    friend std::ostream& operator<<(std::ostream &out, const Sales_item &item);
    friend std::istream& operator>>(std::istream &in, Sales_item &item);
public:
    Sales_item(const std::string &_ID, int copyCnt, double price);
    Sales_item();
    Sales_item& operator=(const Sales_item &that);
    Sales_item operator+(const Sales_item &that)const;
    Sales_item& operator+=(const Sales_item &that);
    bool same_ISBN_with(const Sales_item &that)const noexcept;
    ~Sales_item();

    std::string isbn()const;
private:
    std::string ID;
    int copyCnt;
    double averagePrice;
};

struct compare_Sales_item_with_ISBN
{
    bool operator()(const Sales_item &lhs, const Sales_item &rhs)
    {
        return lhs.isbn() < rhs.isbn();
    }
};

