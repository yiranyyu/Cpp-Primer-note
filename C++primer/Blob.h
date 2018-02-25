#pragma once
#include <memory>
#include <vector>
#include <exception>
#include <initializer_list>
template<typename Val>
class Blob
{
public:
    using value_type = Val;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = value_type*;
    using size_type = typename std::vector<value_type>::size_type;
public:
    Blob();
    template<typename Other>
    Blob(const Blob<Other> &that);
    Blob(std::initializer_list<Val> il);
    ~Blob() = default;

    bool empty() const noexcept;
    size_type size() const noexcept;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    void push_back(const value_type &item);
    void pop_back();
private:
    void checkNotEmpty() const;
    std::shared_ptr<std::vector<Val>> value;
};

template<typename Val>
template<typename Other>
inline Blob<Val>::Blob(const Blob<Other>& that)
    :value(that.value)
{}

template<typename Val>
Blob<Val>::Blob(std::initializer_list<Val> il)
        :value(std::make_shared(il))
{}

template<typename Val>
Blob<Val>::Blob()
    :value(std::make_shared<std::vector<Val>>())
{}

template<typename Val>
inline
typename Blob<Val>::const_reference
Blob<Val>::back() const
{
    checkNotEmpty();
    return value->back();
}

template<typename Val>
inline
Blob::size_type Blob<Val>::size() const noexcept
{
    value->size();
}

template<typename Val>
inline
bool Blob<Val>::empty() const noexcept
{
    return value->empty();
}

template<typename Val>
inline
reference Blob<Val>::front()
{
    checkNotEmpty();
    return value->front();
}

template<typename Val>
inline
void Blob<Val>::checkNotEmpty() const
{
    if (empty())
        throw std::runtime_error("blob is empty");
}

template<typename Val>
inline
typename Blob<Val>::reference
Blob<Val>::back()
{
    checkNotEmpty();
    return value->back();
}

template<typename Val>
const_reference Blob<Val>::front() const
{
    checkNotEmpty();
    return value->front();
}

template<typename Val>
inline
void Blob<Val>::push_back(const Val &item)
{
    value->push_back(item);
}

template<typename Val>
inline
void Blob<Val>::pop_back()
{
    checkNotEmpty();
    value->pop_back();
}
