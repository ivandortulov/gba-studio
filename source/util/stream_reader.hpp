#pragma once

#include <gba_types.h>
#include <string>
#include <cstring>

namespace GBS {
    class StreamReader {
    public:
        StreamReader(const u8* data, const u32 dataSize)
            : data(data), dataSize(dataSize), position(0) {}

    public:
        template<class T>
        inline bool read(T& ptr) {
            return read(ptr, sizeof(T));
        }

        template<class T>
        bool read(T& ptr, size_t size) {
            if (getRemaining() < size) {
                return false;
            }

            memcpy(&ptr, data + position, size);
            position += size;
            return true;
        }

        inline std::string readStr() {
            u16 length;
            if (!read(length) || getRemaining() < length) {
                return "";
            }
            std::string result(reinterpret_cast<const char*>(data + position), length);
            position += length;
            return result;
        }

        inline u32 getRemaining() const {
            return dataSize - position;
        }

        inline u32 getPosition() const {
            return position;
        }

    private:
        const u8* data;
        u32 dataSize;
        u32 position;
    };
}