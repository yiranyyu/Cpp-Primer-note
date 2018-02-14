#pragma once
#include <string>
class Account
{
public:
    static constexpr double rate() noexcept;
    static void setRate(double _rate) noexcept;
private:
    static double INTEREST_RATE;
    static constexpr double initRate() noexcept;
public:
    Account();
    Account(const std::string &_owner);
    Account(const std::string &_owner, double _amount);
    ~Account();

    void calculate() noexcept;
private:
    double amount = 0.0;
    std::string owner;
};

