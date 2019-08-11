#ifndef MAL_REF_COUNT_H
#define MAL_REF_COUNT_H

#include <typeinfo>
#include <iostream>

class RefCounted {
public:
    RefCounted() : m_ref_count(0) {};
    virtual ~RefCounted() = default;

    const RefCounted* ref_increase() const {
        m_ref_count++;
        return this;
    }

    int ref_decrease() const {
        return --m_ref_count;
    }

    int ref_count() const {
        return m_ref_count;
    };

private:
    RefCounted& operator = (const RefCounted&); // no assignments
    mutable int m_ref_count;
};


template <typename T>
class RefCountedPtr {
public:
    RefCountedPtr() : m_object(0) {};

    RefCountedPtr(T* object) : m_object(0) {
        acquire(object);
    }

    RefCountedPtr(const RefCountedPtr& rhs) : m_object(0) {
        acquire(rhs.m_object);
    }

    RefCountedPtr& operator = (const RefCountedPtr& rhs) {
        acquire(rhs.m_object);
        return *this;
    }

    ~RefCountedPtr() {
        release();
    }

    bool operator == (const RefCountedPtr& rhs) const {
        return m_object == rhs.m_object;
    }

    bool operator != (const RefCountedPtr& rhs) const {
        return m_object != rhs.m_object;
    }

    explicit operator bool () const {
        return m_object != nullptr;
    }

    T* operator -> () const {
        return m_object;
    };

    T* ptr() const {
        return m_object;
    }

private:
    void acquire(T* object) {
        if (object != nullptr) {
            object->ref_increase();
        }
        release();
        m_object = object;
    }

    void release() {
        if (m_object != nullptr && (m_object->ref_decrease() == 0)) {
            delete m_object;
        }
    }

    T* m_object;
};

#endif
