#include "StrVec.h"
#include <cmath>
#include <algorithm>
using namespace std;

std::allocator<StrVec::value_type> StrVec::alloc;

StrVec::StrVec()
    :start(nullptr), first_free(nullptr), cap(nullptr)
{}

StrVec::StrVec(initializer_list<value_type> il)
{
    start = alloc.allocate(il.size());
    first_free = cap = move(il.begin(), il.end(), start);
}

StrVec::StrVec(const StrVec & that)
{
    auto pair = alloc_n_copy(that.start, that.first_free);
    start = pair.first;
    first_free = cap = pair.second;
}

StrVec::StrVec(StrVec && that) noexcept
    :start(that.start), first_free(that.first_free), cap(that.cap)
{
    that.start = that.first_free = that.cap = nullptr;
}

StrVec::~StrVec()
{
    free();
}

pair<StrVec::pointer, StrVec::pointer> 
StrVec::alloc_n_copy(const pointer _start, const pointer _end)
{
    pointer newStart = alloc.allocate(_end - _start);
    return { newStart, uninitialized_copy(_start, _end, newStart) };
}

void StrVec::free()
{
    if (start) // pointer pass to deallocate can't be nullptr
    {
        auto cur = start;
        while (cur != first_free)
            alloc.destroy(cur++);
        alloc.deallocate(start, capacity());
    }
}

void StrVec::reallocate()
{
    size_t newCapacity = capacity() + max(size_t(1), capacity()/2);
    pointer newStart = alloc.allocate(newCapacity);

//    auto dest = newStart;
//    auto elem = start;
//    for (size_t i = 0; i != size(); ++i)
//        alloc.construct(dest++, std::move(*elem++));

    auto last = uninitialized_copy(
            make_move_iterator(start),
            make_move_iterator(first_free),
            newStart
    );
    free();
    start = newStart;
//    first_free = dest;
    first_free = last;
    cap = start + newCapacity;
}

void StrVec::push_back(const StrVec::value_type &val)
{
    check_n_alloc();
    alloc.construct(first_free, val);
    ++first_free;
}

void StrVec::push_back(value_type && val)
{
    check_n_alloc();
    alloc.construct(first_free, std::move(val));
    ++first_free;
}

StrVec::pointer StrVec::begin()
{
    return start;
}

StrVec::pointer StrVec::end()
{
    return first_free;
}

const StrVec::pointer StrVec::begin() const
{
    return start;
}

const StrVec::pointer StrVec::end() const
{
    return first_free;
}

StrVec& StrVec::operator=(StrVec that) & // only assign to lvalue
{
    // allocate first in case of self-assignment
    using std::swap;
    swap(*this, that);
    return *this;
}

StrVec::value_type &StrVec::operator[](size_t index)
{
    return start[index];
}

const StrVec::value_type &StrVec::operator[](size_t index) const
{
    return start[index];
}

void swap(StrVec &lhs, StrVec &rhs)
{
    auto &&temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}