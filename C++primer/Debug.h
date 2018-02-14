#pragma once
class Debug
{
public:
    Debug();
    ~Debug();
    
    constexpr bool any();
    
    void setIOError(bool isError);
    void setHardewareError(bool isError);
    void setOtherError(bool isError);

private:
    bool hardwareError;
    bool IOError;
    bool otherError;
};

constexpr bool Debug::any()
{
    return hardwareError || IOError || otherError;
}

inline void Debug::setIOError(bool isError)
{
    IOError = isError;
}

inline void Debug::setHardewareError(bool isError)
{
    hardwareError = isError;
}

inline void Debug::setOtherError(bool isError)
{
    otherError = isError;
}
