#pragma once
#include <stdexcept>
class IO_error : public std::runtime_error
{
private:
    using base_type = std::runtime_error;
    static const std::string DEFAULT_MSG;
public:
    explicit IO_error(const std::string &msg = DEFAULT_MSG)
        :base_type(msg)
    {
        // init with msg string
    }

    explicit IO_error(const char *msg)
        :base_type(msg)
    {
        // init with C-style msg string
    }

    virtual ~IO_error() = default;
};

