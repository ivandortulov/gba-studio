#pragma once

#include <gba_types.h>
#include <string>
#include <vector>

// Base macro for creating EnumValue instances
#define MAKE_ENUM_VALUE(Name, Val) static EnumValue Val{#Val, __COUNTER__};

// Helper macro to concatenate code
#define ENUM_CODE(Name, ...) \
    struct Name { \
        __VA_ARGS__ \
        static std::vector<std::string> keys() { \
            return { #__VA_ARGS__ }; \
        } \
    };

// Main macro that user will call
#define MAKE_ENUM(Name, ...) \
    ENUM_CODE(Name, FOREACH(MAKE_ENUM_VALUE, Name, __VA_ARGS__))

// Helper macros to apply another macro to each argument
#define EXPAND(x) x
#define FOREACH(MACRO, Name, ...) \
    EXPAND(MACRO(Name, __VA_ARGS__))

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

    struct EnumName {
        static EnumValue Value1;
        static EnumValue Value2;
        static EnumValue Value3;

        static std::vector<std::string> keys() {
            return std::vector<std::string>();
        }
    };
}