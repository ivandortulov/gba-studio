#pragma once

#include <string>
#include <vector>

#include "log.hpp"

#define OBJECT(Class, Inherits) \
private: \
    void operator=(const Class &rVal) {} \
public: \
    static void* getClassPtrStatic() { \
        static int basePtr; \
        return &basePtr; \
    } \
    static const std::string getClassStatic() { \
        return std::string(#Class); \
    } \
    static void getInheritanceListStatic(std::vector<std::string>& inheritanceList) { \
        Inherits::getInheritanceListStatic(inheritanceList); \
        inheritanceList.push_back(#Class); \
    } \
    static void getInheritanceListPtrStatic(std::vector<void*>& inheritanceList) { \
        Inherits::getInheritanceListPtrStatic(inheritanceList); \
        inheritanceList.push_back(getClassPtrStatic()); \
    } \
    virtual bool isClass(const std::string& classStr) const override { \
        return (classStr == #Class); \
    } \
    virtual bool isClassPtr(void* ptr) const override { \
        return getClassPtrStatic() == ptr; \
    } \
    virtual void getInheritanceList(std::vector<std::string>& inheritanceList) override { \
        getInheritanceListStatic(inheritanceList); \
    } \
    virtual void getInheritancePtrList(std::vector<void*>& inheritanceList) override { \
        getInheritanceListPtrStatic(inheritanceList); \
    } \
    virtual const std::string getClass() const override { \
        return getClassStatic(); \
    } \
    private:

namespace GBS {

    class Object {
    public:
        virtual ~Object() { };
    public:
        static void* getClassPtrStatic() {
            static int basePtr;
            return &basePtr;
        }

        static const std::string getClassStatic() {
            return std::string("Object");
        }

        static void getInheritanceListStatic(std::vector<std::string>& inheritanceList) {
            inheritanceList.push_back("Object");
        }

        static void getInheritanceListPtrStatic(std::vector<void*>& inheritanceList) {
            inheritanceList.push_back(getClassPtrStatic());
        }

        template <class T>
        static T* cast_to(Object* object) {
            if (!object) {
                return nullptr;
            }

            if (object->isClassPtr(T::getClassPtrStatic())) {
                return reinterpret_cast<T*>(object);
            }

            std::vector<void*> inheritanceListPtr;
            object->getInheritancePtrList(inheritanceListPtr);
            const void* ptrT = T::getClassPtrStatic();

            for (const void* ptr : inheritanceListPtr) {
                if (ptr == ptrT) {
                    return reinterpret_cast<T*>(object);
                }
            }

            return nullptr;
        }

    public:
        virtual bool isClass(const std::string& classStr) const {
            return (classStr == "Object");
        }

        virtual bool isClassPtr(void* ptr) const {
            return getClassPtrStatic() == ptr;
        }

        virtual void getInheritanceList(std::vector<std::string>& inheritanceList) {
            getInheritanceListStatic(inheritanceList);
        }

        virtual void getInheritancePtrList(std::vector<void*>& inheritanceList) {
            getInheritanceListPtrStatic(inheritanceList);
        }

        virtual const std::string getClass() const {
            return "Object";
        }
    };

}