#pragma once

#define LOG_DEBUG(message, ...) \
    GBS::Logger::log(GBS::LOG_DEBUG, message, ## __VA_ARGS__)

#define LOG_ERR(message, ...) \
    GBS::Logger::log(GBS::LOG_ERROR, message, ## __VA_ARGS__)

namespace GBS {

    enum ELogLevel {
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARN,
        LOG_INFO,
        LOG_DEBUG,
    };

    class Logger {
        public:
            Logger();
            ~Logger();

        public:
            static void log(ELogLevel level, const char* ptr, ...);
    };
}