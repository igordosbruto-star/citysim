#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <chrono>

// Desabilitar TODAS as macros problemáticas do Windows ANTES de qualquer coisa
#ifdef _WIN32
    #ifdef ERROR
        #undef ERROR
    #endif
    #ifdef DEBUG
        #undef DEBUG
    #endif  
    #ifdef INFO
        #undef INFO
    #endif
    #ifdef TRACE
        #undef TRACE
    #endif
    #ifdef WARNING
        #undef WARNING
    #endif
    #ifdef FATAL
        #undef FATAL
    #endif
#endif

namespace CitySim {

// Enum com prefixo para evitar absolutamente qualquer conflito
enum class LogLevel {
    LTrace,
    LDebug, 
    LInfo,
    LWarning,
    LError,
    LFatal
};

class Logger {
public:
    static Logger& getInstance();
    
    void initialize(const std::string& logFile = "");
    void shutdown();
    
    void log(LogLevel level, const std::string& message);
    void log(LogLevel level, const char* format, ...);
    
    // Métodos específicos por nível
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void fatal(const std::string& message);
    
    void setLevel(LogLevel level) { m_logLevel = level; }
    void setConsoleOutput(bool enable) { m_consoleOutput = enable; }
    void setFileOutput(bool enable) { m_fileOutput = enable; }

private:
    Logger() = default;
    ~Logger() = default;
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::string getCurrentTime();
    std::string levelToString(LogLevel level);
    std::string levelToColor(LogLevel level);
    void writeToConsole(LogLevel level, const std::string& message);
    void writeToFile(const std::string& message);
    
    LogLevel m_logLevel = LogLevel::LInfo;
    bool m_consoleOutput = true;
    bool m_fileOutput = false;
    std::ofstream m_logFile;
    std::mutex m_mutex;
};

// Macros COMPLETAMENTE seguras
#define LOG_TRACE(message) CitySim::Logger::getInstance().trace(message)
#define LOG_DEBUG(message) CitySim::Logger::getInstance().debug(message)
#define LOG_INFO(message) CitySim::Logger::getInstance().info(message)
#define LOG_WARNING(message) CitySim::Logger::getInstance().warning(message)
#define LOG_ERROR(message) CitySim::Logger::getInstance().error(message)
#define LOG_FATAL(message) CitySim::Logger::getInstance().fatal(message)

#define LOG_TRACE_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LTrace, format, ##__VA_ARGS__)
#define LOG_DEBUG_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LDebug, format, ##__VA_ARGS__)
#define LOG_INFO_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LInfo, format, ##__VA_ARGS__)
#define LOG_WARNING_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LWarning, format, ##__VA_ARGS__)
#define LOG_ERROR_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LError, format, ##__VA_ARGS__)
#define LOG_FATAL_F(format, ...) CitySim::Logger::getInstance().log(CitySim::LogLevel::LFatal, format, ##__VA_ARGS__)

} // namespace CitySim