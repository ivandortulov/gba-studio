#pragma once

#include <string>
#include <vector>

#define OBJECT(m_class, m_inherits) \
private: \
    void operator=(const m_class &p_rval) {} \
public: \
    virtual const std::string getClass() const override{ \
        return std::string(#m_class); \
    } \
    virtual bool isClassPtr(void* p_ptr) const override { \
      return getClassPtrStatic() == p_ptr; \
    } \
    static inline const std::string getClassStatic() { \
		return std::string(#m_class); \
	} \
    static inline void* getClassPtrStatic() { \
      static int basePtr; \
      return &basePtr; \
    } \
    static inline const std::string getParentClassStatic() { \
		return m_inherits::getClassStatic(); \
	} \
    static void getInheritanceListStatic(std::vector<std::string> *p_inheritance_list) { \
		m_inherits::getInheritanceListStatic(p_inheritance_list); \
		p_inheritance_list->push_back(std::string(#m_class)); \
	} \
    static std::string inheritsStatic() { \
		return std::string(#m_inherits); \
	} \
    private:

namespace GBS {

    class Object {
    public:
        virtual ~Object() { };
    public:
        static inline void* getClassPtrStatic() {
            static int basePtr;
            return &basePtr;
        }

        static inline const std::string getClassStatic() {
            return std::string("Object");
        }

        static void getInheritanceListStatic(std::vector<std::string>* p_inheritance_list) {
            p_inheritance_list->push_back("Object");
        }

        virtual bool isClass(const std::string& p_class) const {
            return (p_class == "Object");
        }

        virtual bool isClassPtr(void* p_ptr) const {
            return getClassPtrStatic() == p_ptr;
        }

        virtual void getInheritanceList(std::vector<std::string>* p_inheritance_list) {
            getInheritanceListStatic(p_inheritance_list);
        }

        virtual const std::string getClass() const {
            return "Object";
        }

        template <class T>
        static T* cast_to(Object* p_object) {
            if (p_object && p_object->isClassPtr(T::getClassPtrStatic())) {
                return static_cast<T*>(p_object);
            }
            return nullptr;
        }

    protected:
        std::string className;
    };

}