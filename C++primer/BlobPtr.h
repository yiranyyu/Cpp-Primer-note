//
// Created by yirany on 2018/2/25.
//
#pragma once
#ifndef C_PRIMER_BLOBPTR_H
#define C_PRIMER_BLOBPTR_H
#include <memory>
#include <exception>
#include "Blob.h"
template<typename T> class Blob;

template <class Val>
class BlobPtr
{
private:
    static const std::string INDEX_OUT_OF_RANGE;
public:
    BlobPtr();
    BlobPtr(Blob<Val> &blob, size_t _index = 0);

    bool operator==(const BlobPtr &that);
    bool operator!=(const BlobPtr &that);
    bool operator<(const BlobPtr<Val> &that);
    bool operator>(const BlobPtr<Val> &that);
    Val& operator[](size_t pos);
    const Val& operator[](size_t pos) const;
    Val& operator*() const;
    Val* operator->() const;
    BlobPtr& operator++();
    BlobPtr operator++(int);
    BlobPtr& operator--();
    BlobPtr operator--(int);
    int operator-(const BlobPtr<Val> &that) const;
    BlobPtr<Val> operator-(size_t i) const;
    BlobPtr<Val>& operator-=(size_t i);
    BlobPtr<Val> operator+(size_t i) const;
    BlobPtr<Val>& operator+=(size_t i);
private:
    void checkIndex(size_t toCheck, const std::string &msg) const;
    void checkSameContainer(const BlobPtr<Val> &that) const;
    std::weak_ptr<std::vector<Val>> data;
    size_t index;
};

template <typename Val>
const std::string BlobPtr<Val>::INDEX_OUT_OF_RANGE = "index out of range";

template<class Val>
BlobPtr<Val>::BlobPtr()
    :index(0)
{}

template<class Val>
BlobPtr<Val>::BlobPtr(Blob<Val> &blob, size_t _index)
    :data(blob.value), index(_index)
{
    auto v = blob;
    checkIndex(index+1, INDEX_OUT_OF_RANGE);
}

template<class Val>
inline bool BlobPtr<Val>::operator==(const BlobPtr<Val> & that)
{
    return (*data.lock()) == (*that.data.lock()) && index == that.index;
}

template<class Val>
Val &BlobPtr<Val>::operator*() const
{
    checkIndex(index, INDEX_OUT_OF_RANGE);
    auto ptr = data.lock();
    return (*ptr)[index];
}

template<class Val>
inline Val* BlobPtr<Val>::operator->() const
{
    return &(**this);
}

template<class Val>
inline
BlobPtr<Val>& BlobPtr<Val>::operator++()
{
    checkIndex(index, "Cannot incre pointer at end");
    ++index;
    return *this;
}

template<class Val>
BlobPtr<Val> BlobPtr<Val>::operator++(int)
{
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class Val>
BlobPtr<Val>& BlobPtr<Val>::operator--()
{
    --index;
    try 
    {
        checkIndex(index, "Cannot decre pointer at begin");
    } 
    catch (std::out_of_range&) 
    {
        ++index;
        throw;
    }
    return *this;
}

template<class Val>
BlobPtr<Val> BlobPtr<Val>::operator--(int)
{
    auto temp = *this;
    --(*this);
    return temp;
}

template<class Val>
inline int BlobPtr<Val>::operator-(const BlobPtr<Val>& that) const
{
    checkSameContainer(that);
    return static_cast<int>(this->index) - static_cast<int>(that.index);
}

template<class Val>
void BlobPtr<Val>::checkIndex(size_t toCheck, const std::string &msg) const
{
    auto ptr = data.lock();
    if (!ptr)
        throw std::runtime_error("unbound BlobPtr");
    if (toCheck >= ptr->size())
        throw std::out_of_range(msg);
}

template<class Val>
inline void BlobPtr<Val>::checkSameContainer(const BlobPtr<Val>& that) const
{
    if( data.lock().get() != that.data.lock().get())
        throw std::runtime_error("canont compare pointer of different contianers");
}

template<class Val>
bool BlobPtr<Val>::operator!=(const BlobPtr &that)
{
    return !(*this == that);
}

template<class Val>
inline bool BlobPtr<Val>::operator<(const BlobPtr<Val>& that)
{
    checkSameContainer(that);
    return this->index < that.index;
}

template<class Val>
bool BlobPtr<Val>::operator>(const BlobPtr<Val> &that)
{
    return !(*this < that || *this == that);
}

template<class Val>
inline Val & BlobPtr<Val>::operator[](size_t pos)
{
    return data.lock()->operator[](pos + this->index);
}

template<class Val>
const Val &BlobPtr<Val>::operator[](size_t pos) const
{
    return data.lock()->operator[](pos + this->index);
}

template<class Val>
BlobPtr<Val> BlobPtr<Val>::operator-(size_t i) const
{
    return BlobPtr<Val>(*this) -= i;
}

template<class Val>
BlobPtr<Val>& BlobPtr<Val>::operator-=(size_t i)
{
    index -= i;
    checkIndex(index+1, INDEX_OUT_OF_RANGE);
    return *this;
}

template<class Val>
BlobPtr<Val> BlobPtr<Val>::operator+(size_t i) const
{
    return BlobPtr<Val>(*this) += i;
}

template<class Val>
BlobPtr<Val>& BlobPtr<Val>::operator+=(size_t i)
{
    index += i;
    checkIndex(index+1, INDEX_OUT_OF_RANGE);
    return *this;
}

#endif //C_PRIMER_BLOBPTR_H
