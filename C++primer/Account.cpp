#include "stdafx.h"
#include "Account.h"

double Account::INTEREST_RATE = initRate();

constexpr double Account::rate() noexcept
{
    return INTEREST_RATE;
}

inline void Account::setRate(double _rate) noexcept
{
    INTEREST_RATE = _rate;
}


constexpr double Account::initRate() noexcept
{
    return 0.05;
}

Account::Account() = default;

Account::Account(const std::string & _owner)
    :owner(_owner)
{}

Account::Account(const std::string & _owner, double _amount)
    :amount(_amount), owner(_owner)
{}


Account::~Account() = default;

inline void Account::calculate() noexcept
{
    amount += amount * rate();
}
