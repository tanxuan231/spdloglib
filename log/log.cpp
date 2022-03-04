#include <stdio.h>
#include <stdarg.h>
#include "log.h"
#include "../include/singleton.h"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/fmt/bundled/printf.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
class LogSeivice
{
    SINGLETON(LogSeivice)
public:
    void InitLogService(const std::string& fileName, BLogType type = BLOG_CONSOLE,
                        int logLevel = spdlog::level::trace);

    void Close();

    template <typename... Args>
    void Log(const spdlog::source_loc& loc, spdlog::level::level_enum lvl,
            const char* fmt, const Args &... args);
    template <typename... Args>
    void Log(const char *filename_in, int line_in, const char *funcname_in, spdlog::level::level_enum lvl,
            const char* fmt, const Args &... args);

    template <typename... Args>
    void Printf(const spdlog::source_loc& loc, spdlog::level::level_enum lvl,
                const char* fmt, const Args &... args);

    std::shared_ptr<spdlog::logger> GetLogger() const;

private:
    BLogType m_type_;
    std::shared_ptr<spdlog::logger> m_logger;
    std::shared_ptr<spdlog::logger> m_logger_;
};


LogSeivice::LogSeivice() = default;
LogSeivice::~LogSeivice()
{
}

std::shared_ptr<spdlog::logger> LogSeivice::GetLogger() const
{
    return m_logger;
}

void LogSeivice::InitLogService(const std::string &fileName, BLogType type, int logLevel)
{
    switch ((int)type)
    {
    case BLOG_FILE:
        m_logger = spdlog::rotating_logger_mt<spdlog::async_factory>("rotating_logger", fileName, 1024 * 1024 * 5, 3);
        break;
    case BLOG_ALL:
        //m_logger = spdlog::daily_logger_mt<spdlog::async_factory>("logger", fileName, 2, 30);
        m_logger = spdlog::rotating_logger_mt<spdlog::async_factory>("rotating_logger", fileName, 1024 * 1024 * 5, 3);
        m_logger_ = spdlog::stdout_color_mt<spdlog::async_factory>("console");
        m_logger_->set_level(static_cast<spdlog::level::level_enum>(logLevel));
        m_logger_->flush_on(spdlog::level::err);
        break;
    case BLOG_CONSOLE:
        m_logger = spdlog::stdout_color_mt<spdlog::async_factory>("console");
    default:
        break;
    }

    m_type_ = type;
    m_logger->set_level(static_cast<spdlog::level::level_enum>(logLevel));
    m_logger->flush_on(spdlog::level::err);
    spdlog::flush_every(std::chrono::seconds(3));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] [%s:%# %!] %v");
}

void LogSeivice::Close()
{
    spdlog::error("spdlog exit.");
    spdlog::shutdown();
    spdlog::drop_all();    
}

template <typename... Args>
void LogSeivice::Log(const char *filename_in, int line_in, const char *funcname_in, spdlog::level::level_enum lvl,
        const char* fmt, const Args &... args)
{
    spdlog::source_loc loc = spdlog::source_loc(filename_in, line_in, funcname_in);

    if (m_type_ == BLOG_ALL){
        m_logger->log(loc, lvl, fmt::sprintf(fmt, args...).c_str());
        m_logger_->log(loc, lvl, fmt::sprintf(fmt, args...).c_str());
    } else {
        m_logger->log(loc, lvl, fmt::sprintf(fmt, args...).c_str());
    }
}

#define LogServiceInstance Singleton<LogSeivice>::Instance()

#define SPDLOG_BASE(logger, level, filename, line, func, ...) (logger).Log(filename, line, func, level, __VA_ARGS__)

#define LOG_TRACE(filename, line, func, ...)         SPDLOG_BASE(LogServiceInstance, spdlog::level::trace, filename, line, func, __VA_ARGS__)
#define LOG_DEBUG(filename, line, func, ...)         SPDLOG_BASE(LogServiceInstance, spdlog::level::debug, filename, line, func, __VA_ARGS__)
#define LOG_INFO(filename, line, func, ...)          SPDLOG_BASE(LogServiceInstance, spdlog::level::info, filename, line, func, __VA_ARGS__)
#define LOG_WARN(filename, line, func, ...)          SPDLOG_BASE(LogServiceInstance, spdlog::level::warn,  filename, line, func, __VA_ARGS__)
#define LOG_ERROR(filename, line, func, ...)         SPDLOG_BASE(LogServiceInstance, spdlog::level::err,  filename, line, func, __VA_ARGS__)
#define LOG_CRITICAL(filename, line, func, ...)      SPDLOG_BASE(LogServiceInstance, spdlog::level::critical,  filename, line, func, __VA_ARGS__)


static bool IsSpdlogInited = false;

void InitSpdLog(const char* fileName, enum BLogType type, int logLevel)
{
    LogServiceInstance.InitLogService(fileName, type, logLevel);
    IsSpdlogInited = true;
}

void DeinitSpdLog()
{
    if (IsSpdlogInited) {
        LogServiceInstance.Close();        
    }
}

static void SpdLogHandler(int level, const char *filename, int line, const char *func, const char *format, va_list args)
{
    char out[4096] = {0};
    vsnprintf(out, sizeof(out), format, args);
    switch (level) {
    case LOG_INFO:        
        LOG_INFO(filename, line, func, "%s", out);
        break;
    case LOG_DEBUG:
        LOG_DEBUG(filename, line, func, "%s", out);
        break;
    case LOG_TRACE:
        LOG_TRACE(filename, line, func, "%s", out);
        break;
    case LOG_WARNING:
        LOG_WARN(filename, line, func, "%s", out);
        break;
    case LOG_ERROR:
        LOG_ERROR(filename, line, func, "%s", out);
        break;
    case LOG_CRITICAL:
        LOG_CRITICAL(filename, line, func, "%s", out);
        break;
    default:
        LOG_INFO(filename, line, func, "%s", out);
        break;
    }
}

void blogInternal(int level, const char *filename, int line, const char *func, const char *format, ...)
{
    if (!IsSpdlogInited) {
        printf("spdlog is not inited\n");
        return;
    }

    va_list args;

    va_start(args, format);
    SpdLogHandler(level, filename, line, func, format, args);
    va_end(args);
}