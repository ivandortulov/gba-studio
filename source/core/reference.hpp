#pragma once

#include <gba_types.h>
#include <algorithm>

#include "object.hpp"

namespace GBS {

  class Reference : public Object {
    OBJECT(Reference, Object)

  public:
    Reference() : refCount(0) { }

  public:
    void addRef() {
      refCount++;
    }

    bool release() {
      return --refCount <= 0;
    }

  public:
    u32 refCount;
  };

  // Template class for RefPointer
  template<typename T>
  class RefPointer {
  public:
    explicit RefPointer(T* p = nullptr) : ptr(p) {
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
    RefPointer(const RefPointer<U>& other) : ptr(nullptr) {
      T* newPtr = Object::cast_to<T>(other.get());
      if (newPtr != ptr) {
        if (ptr && ptr->release()) {
          delete ptr;
        }
        ptr = newPtr;
        if (ptr) {
          ptr->addRef();
        }
      }
    }

    ~RefPointer() {
      if (ptr && ptr->release()) {
        delete ptr;
      }
    }

  public:
    RefPointer& operator=(T* otherPtr) {
      if (ptr != otherPtr) {
        if (ptr && ptr->release()) {
          delete ptr;
        }
        ptr = otherPtr;
        if (ptr) {
          ptr->addRef();
        }
      }
      return *this;
    }

    RefPointer& operator=(const RefPointer& other) {
      if (this == &other) {
        return *this;
      }
      if (ptr != other.ptr) {
        if (ptr && ptr->release()) {
          delete ptr;
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

    operator bool() const { return ptr != nullptr; }

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
        if (ptr && ptr->release()) {
          delete ptr;
        }
        ptr = newPtr;
        if (ptr) {
          ptr->addRef();
        }
      }
      return *this;
    }

    inline bool isNull() const {
      return ptr == nullptr;
    }

  private:
    T* ptr;
  };
}
