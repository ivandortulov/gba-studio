#pragma once

#define LOG_DEBUG(message, ...) \
    GBS::Logger::log(GBS::Debug, message, ## __VA_ARGS__)

#define LOG_ERR(message, ...) \
    GBS::Logger::log(GBS::Error, message, ## __VA_ARGS__)

#define LOG_WARN(message, ...) \
    GBS::Logger::log(GBS::Warning, message, ## __VA_ARGS__)

namespace GBS {

    enum ELogLevel {
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
    };

    class Logger {
    public:
        Logger();
        ~Logger();

    public:
        static void log(ELogLevel level, const char* ptr, ...);
    };
}