#pragma once
class Tools
{
public:
    template <typename T>
    static T min(const T &lhs, const T &rhs)
    {
        return lhs < rhs ? lhs : rhs;
    }

    template <typename T>
    static T max(const T &lhs, const T &rhs)
    {
        return lhs < rhs ? rhs : lhs;
    }

private:
    Tools();
};

