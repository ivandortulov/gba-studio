#pragma once

#include <gba_types.h>

#include "object.hpp"

namespace GBS {
    // Forward declaration for the control block
    class RefCount;

    // Reference counted base class
    class Reference : public Object {
        OBJECT(Reference, Object)

    public:
        Reference() : refCount(0) {}

    public:
        void addRef() {
            refCount++;
        }

        void release() {
            if (--refCount == 0) {
                delete this;
            }
        }

    private:
        u32 refCount;
    };

    // Template class for RefPointer
    template<typename T>
    class RefPointer {
    public:
        RefPointer(T* p = nullptr) : ptr(p) {
            if (ptr) {
                ptr->addRef();
            }
        }

        RefPointer(const RefPointer& other) : ptr(other.ptr) {
            if (ptr) {
                ptr->addRef();
            }
        }

        template<typename U>
        RefPointer(const RefPointer<U>& other) {
            T* newPtr = Object::cast_to<T>(other.get());
            if (newPtr != ptr) {
                if (ptr) {
                    ptr->release();
                }
                ptr = newPtr;
                if (ptr) {
                    ptr->addRef();
                }
            }
        }

        ~RefPointer() {
            if (ptr) {
                ptr->release();
            }
        }

    public:
        RefPointer& operator=(const RefPointer& other) {
            if (this == &other) {
                return *this;
            }
            if (this->ptr != other.ptr) {
                if (ptr) {
                    ptr->release();
                }
                ptr = other.ptr;
                if (ptr) {
                    ptr->addRef();
                }
            }
            return *this;
        }

        T* operator->() const {
            return ptr;
        }

        T& operator*() const {
            return *ptr;
        }

        T* get() const {
            return ptr;
        }

        bool operator==(const RefPointer<T>& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const RefPointer<T>& other) const {
            return ptr != other.ptr;
        }

        template<typename U>
        RefPointer& operator=(const RefPointer<U>& other) {
            T* newPtr = Object::cast_to<T>(other.get());
            if (newPtr != ptr) {
                if (ptr) {
                    ptr->release();
                }
                ptr = newPtr;
                if (ptr) {
                    ptr->addRef();
                }
            }
            return *this;
        }

    private:
        T* ptr;
    };

}