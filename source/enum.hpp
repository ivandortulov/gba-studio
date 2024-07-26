#pragma once

#include <gba_types.h>
#include <string>
#include <vector>

#define ENUM(...) \
    private: \
        static void registerValue(const std::string& name, s32 value) { \
            constants.push_back({ name, value }); \
        } \
        static std::vector<EnumValue> constants; \
    public:

#define ENUM_VALUE(Name, Value) \
    public: \
        static const EnumValue Name;

namespace GBS {
    struct EnumValue {
        u32 value;
        std::string name;

        EnumValue(const std::string& name, u32 value) {
            this->name = name;
            this->value = value;
        }

        explicit operator u32() const;
    };

    struct ETestEnum {
        ENUM(Value1, Value2, Value3)
    };
}