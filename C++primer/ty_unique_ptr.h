#pragma once

template <typename Val>
struct ty_unique_ptr_deleter
{
    void operator()(Val *ptr)
    {
        delete ptr;
    }
};

template <typename Val, typename Deleter = ty_unique_ptr_deleter<Val>>
class ty_unique_ptr
{
public:
    ty_unique_ptr(Val *_ptr, Deleter deleter = Deleter());
    ~ty_unique_ptr();
private:
    Val *ptr;
    Deleter deleter;
};


template <typename Val, typename Deleter>
ty_unique_ptr<Val, Deleter>::ty_unique_ptr(Val *_ptr, Deleter _deleter)
    :ptr(_ptr), deleter(_deleter)
{}

template<typename Val, typename Deleter>
ty_unique_ptr<Val, Deleter>::~ty_unique_ptr()
{
    deleter(ptr);
}
