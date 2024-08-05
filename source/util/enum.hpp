#pragma once

#include <gba_types.h>
#include <string>
#include <vector>


#define ENUM(Name) \
    static std::vector<std::string> keys(); \
    static std::vector<u32> values(); \
    static u32 size();


#define ENUM_VALUE(Name) \
    public: \
        static const EnumValue Name; \
    private:


namespace GBS {
    struct EnumValue {
        u16 value;
        std::string name;

        EnumValue(const std::string& name, u16 value) {
            this->name = name;
            this->value = value;
        }

        explicit operator u16() const;
    };

    struct ETestEnum {
        ENUM(ETestEnum)

        ENUM_VALUE(Value1)
        ENUM_VALUE(Value2)
    };
}