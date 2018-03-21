#pragma once

template<typename Resource>
struct ReferenceCountBase
{
    size_t count = 0;
    ReferenceCountBase() = default;
    ReferenceCountBase(size_t _count) 
        : count(_count) 
    {}

    virtual void decreReference(Resource *ptr)
    {
        if (--count == 0)
            delete ptr;
    }
};

template <typename Resource, typename Deleter>
struct ReferenceCountWithDeleter: public ReferenceCountBase<Resource>
{
    using Mybase = ReferenceCountBase<Resource>;
    Deleter deleter;
    bool initialized = false;
    ReferenceCountWithDeleter() = default;
    ReferenceCountWithDeleter(Deleter _deleter)
        :deleter(_deleter), initialized(false)
    {}

    virtual void decreReference(Resource *ptr)
    {
        if (--count == 0)
            initialized ? deleter(ptr) : delete ptr;
    }
};

template <typename T>
class ty_shared_ptr
{
public:
    ty_shared_ptr();

    ty_shared_ptr(T *_ptr);

    template <typename Deleter> 
    ty_shared_ptr(T *_ptr, Deleter deleter);

    template <typename Other> 
    ty_shared_ptr(Other *_ptr);

    template <typename Other, typename Deleter> 
    ty_shared_ptr(Other *_ptr, Deleter deleter);

    ty_shared_ptr(const ty_shared_ptr &that);

    template <typename Other> 
    ty_shared_ptr(const ty_shared_ptr<Other> &that);

    ty_shared_ptr& operator=(const ty_shared_ptr &that);
    template <typename Other> ty_shared_ptr& operator=(const ty_shared_ptr<Other> &that);
    ~ty_shared_ptr();

    T& operator*()const;
    T* operator->()const noexcept;
    T* get()const noexcept;
private:
    T *ptr;
    ReferenceCountBase<T> *ref_count;
};

template<typename T>
ty_shared_ptr<T>::ty_shared_ptr()
    :ptr(nullptr), ref_count(new ReferenceCountBase<T>)
{}

template<typename T>
ty_shared_ptr<T>::ty_shared_ptr(T * _ptr)
    :ptr(_ptr), ref_count(new ReferenceCountBase<T>)
{}

template<typename T>
template<typename Deleter>
inline ty_shared_ptr<T>::ty_shared_ptr(T * _ptr, Deleter deleter)
    :ptr(_ptr), ref_count(new ReferenceCountWithDeleter<T, Deleter>(deleter))
{}

template<typename T>
template<typename Other>
ty_shared_ptr<T>::ty_shared_ptr(Other * _ptr)
    :ptr(_ptr), ref_count(new ReferenceCountBase<T>)
{}

template<typename T>
template<typename Other, typename Deleter>
ty_shared_ptr<T>::ty_shared_ptr(Other * _ptr, Deleter deleter)
    :ptr(_ptr), ref_count(new ReferenceCountWithDeleter<T, Deleter>(deleter))
{}

template<typename T>
ty_shared_ptr<T>::ty_shared_ptr(const ty_shared_ptr &that)
    :ptr(that.ptr), ref_count(that.ref_count)
{
    ref_count->count += 1;
}

template<typename T>
ty_shared_ptr<T>& ty_shared_ptr<T>::operator=(const ty_shared_ptr & that)
{
    that.ref_count->count += 1;
    ref_count->decreReference(ptr);
    if (ref_count->count == 0)
        delete ref_count;
    this.ptr = that.ptr;
    this.ref_count = that.ref_count;
    return *this;
}

template<typename T>
ty_shared_ptr<T>::~ty_shared_ptr()
{
    ref_count->decreReference(ptr);
    if (ref_count->count == 0)
        delete ref_count;
}

template<typename T>
inline T & ty_shared_ptr<T>::operator*() const
{
    return *ptr;
}

template<typename T>
inline T * ty_shared_ptr<T>::operator->() const noexcept
{
    return ptr;
}

template<typename T>
inline T * ty_shared_ptr<T>::get() const noexcept
{
    return ptr;
}

template<typename T>
template<typename Other>
ty_shared_ptr<T>::ty_shared_ptr(const ty_shared_ptr<Other> &that)
    :ptr(that.ptr), ref_count(that.ref_count)
{
    ref_count->count += 1;
}