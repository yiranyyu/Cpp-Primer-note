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

    Val& operator*();
    const Val& operator*()const;
    BlobPtr& operator++() noexcept;
    BlobPtr operator++(int);
    BlobPtr& operator--() noexcept;
    BlobPtr operator--(int);
private:
    void checkIndex(const std::string &msg) const;
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
    checkIndex(INDEX_OUT_OF_RANGE);
}

template<class Val>
Val &BlobPtr<Val>::operator*()
{
    checkIndex(INDEX_OUT_OF_RANGE);
    auto ptr = data.lock();
    return (*ptr)[index];
}

template<class Val>
inline
BlobPtr& BlobPtr<Val>::operator++() noexcept
{
    ++index;
    return *this;
}

template<class Val>
BlobPtr BlobPtr<Val>::operator++(int)
{
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class Val>
BlobPtr &BlobPtr<Val>::operator--() noexcept
{
    --index;
    return *this;
}

template<class Val>
BlobPtr BlobPtr<Val>::operator--(int)
{
    auto temp = *this;
    --(*this);
    return temp;
}

template<class Val>
const Val &BlobPtr<Val>::operator*() const
{
    checkIndex(INDEX_OUT_OF_RANGE);
    auto ptr = data.lock();
    return (*ptr)[index];
}

template<class Val>
void BlobPtr<Val>::checkIndex(const std::string &msg) const
{
    auto ptr = data.lock();
    if (!ptr)
        throw std::runtime_error("unbound BlobPtr");
    if (index >= ptr->size())
        throw std::out_of_range(msg);
}


#endif //C_PRIMER_BLOBPTR_H
