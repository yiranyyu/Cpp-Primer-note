#pragma once
#include <memory>
#include <string>
class StrVec
{
public:
    using value_type = std::string;
    using pointer = value_type * ;
    using const_pointer = const value_type * ;
private:
    static std::allocator<value_type> alloc;
public:
    StrVec();
    StrVec(std::initializer_list<value_type> il);
    StrVec(const StrVec &that);
    StrVec(StrVec &&that) noexcept;
    StrVec& operator=(StrVec that) &;// only assign to lvalue
    StrVec& operator=(std::initializer_list<std::string> il)&;
    ~StrVec();

    bool operator==(const StrVec &that);
    bool operator!=(const StrVec &that);
    bool operator<(const StrVec &that);
    bool operator>(const StrVec &that);
    size_t size()const noexcept;
    size_t capacity() const noexcept;
    void push_back(const value_type &val);
    void push_back(value_type &&val);
    pointer begin();
    pointer end();
    const pointer begin() const;
    const pointer end() const;
    value_type& operator[](size_t index);
    const value_type& operator[](size_t index) const;
private:
    void check_n_alloc();
    std::pair<pointer, pointer> alloc_n_copy(const const_pointer _start, const const_pointer _end);
    bool sameContent(const StrVec &that);
    void free();
    void reallocate();
    pointer start;
    pointer first_free;
    pointer cap;
};

inline
void StrVec::check_n_alloc()
{
    if (size() == capacity())
        reallocate();
}

inline bool StrVec::operator<(const StrVec & that)
{
    auto cur = begin(), thatCur = that.begin(),
         last = end(), thatLast = that.end();
    while (cur != last && thatCur != thatLast)
    {
        if (*cur != *thatCur)
            return *cur < *thatCur;
        ++cur, ++thatCur;
    }
    return thatCur != thatLast;
}

inline bool StrVec::operator>(const StrVec & that)
{
    return !(*this < that || *this == that);
}

inline
size_t StrVec::size() const noexcept
{
    return first_free - start;
}

inline
size_t StrVec::capacity() const noexcept
{
    return cap - start;
}