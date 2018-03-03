#pragma once
#include <memory>
#include <string>
class StrVec
{
public:
    using value_type = std::string;
    using pointer = value_type * ;
private:
    static std::allocator<value_type> alloc;
public:
    StrVec();
    StrVec(std::initializer_list<value_type> il);
    StrVec(const StrVec &that);
    StrVec(StrVec &&that) noexcept;
    StrVec& operator=(StrVec that) &;// only assign to lvalue
    ~StrVec();

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
    std::pair<pointer, pointer> alloc_n_copy(const pointer _start, const pointer _end);
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
