#pragma once

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

enum {
    LOG_CRITICAL = 100,
    LOG_ERROR = 200,
    LOG_WARNING = 300,
    LOG_INFO = 400,
    LOG_DEBUG = 500,
    LOG_TRACE = 600
};

enum BLogLevel
{
    BLOG_LEVEL_TRACE = 0,
    BLOG_LEVEL_DEBUG,
    BLOG_LEVEL_INFO,
    BLOG_LEVEL_WARN,
    BLOG_LEVEL_ERROR,
    BLOG_LEVEL_CRITICAL,
    BLOG_LEVEL_OFF
};

enum BLogType{
    BLOG_CONSOLE,   // output console only
    BLOG_FILE,      // output file only
    BLOG_ALL        // output file and console
};

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void InitSpdLog(const char* fileName, enum BLogType type, int logLevel);

EXPORT void DeinitSpdLog();

EXPORT void blogInternal(int level, const char *filename, int line, const char *func, const char *format, ...);

#define blog(logLevel, ...) blogInternal(logLevel, __FILE__, __LINE__, __func__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif