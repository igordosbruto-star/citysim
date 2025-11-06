#include "Utils/Logger.hpp"
#include <cstdarg>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace CitySim {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(const std::string& logFile) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    if (!logFile.empty()) {
        m_logFile.open(logFile, std::ios::out | std::ios::app);
        if (m_logFile.is_open()) {
            m_fileOutput = true;
            std::cout << "Log file opened: " + logFile << std::endl;
        } else {
            std::cerr << "Failed to open log file: " << logFile << std::endl;
        }
    }
}

void Logger::shutdown() {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    if (m_logFile.is_open()) {
        log(LogLevel::LInfo, "Shutting down logger...");
        m_logFile.close();
    }
    m_fileOutput = false;
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    
    #ifdef _WIN32
        struct tm timeinfo;
        localtime_s(&timeinfo, &time_t);
        ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    #else
        struct tm* timeinfo = localtime(&time_t);
        ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    #endif
    
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::LTrace:   return "TRACE";
        case LogLevel::LDebug:   return "DEBUG";
        case LogLevel::LInfo:    return "INFO";
        case LogLevel::LWarning: return "WARNING";
        case LogLevel::LError:   return "ERROR";
        case LogLevel::LFatal:   return "FATAL";
        default:                 return "UNKNOWN";
    }
}

std::string Logger::levelToColor(LogLevel level) {
    switch (level) {
        case LogLevel::LTrace:   return "\033[37m";
        case LogLevel::LDebug:   return "\033[36m";
        case LogLevel::LInfo:    return "\033[32m";
        case LogLevel::LWarning: return "\033[33m";
        case LogLevel::LError:   return "\033[31m";
        case LogLevel::LFatal:   return "\033[35m";
        default:                 return "\033[0m";
    }
}

void Logger::writeToConsole(LogLevel level, const std::string& message) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD color = 7;
        
        switch (level) {
            case LogLevel::LTrace:   color = 8; break;
            case LogLevel::LDebug:   color = 11; break;
            case LogLevel::LInfo:    color = 10; break;
            case LogLevel::LWarning: color = 14; break;
            case LogLevel::LError:   color = 12; break;
            case LogLevel::LFatal:   color = 13; break;
        }
        
        SetConsoleTextAttribute(hConsole, color);
        std::cout << message << std::endl;
        SetConsoleTextAttribute(hConsole, 7);
    #else
        std::cout << levelToColor(level) << message << "\033[0m" << std::endl;
    #endif
}

void Logger::writeToFile(const std::string& message) {
    if (m_fileOutput && m_logFile.is_open()) {
        m_logFile << message << std::endl;
        m_logFile.flush();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < m_logLevel) return;
    
    std::lock_guard<std::mutex> lock(m_mutex);
    
    std::string timestamp = getCurrentTime();
    std::string levelStr = levelToString(level);
    
    std::stringstream formattedMessage;
    formattedMessage << "[" << timestamp << "] "
                     << "[" << levelStr << "] "
                     << message;
    
    std::string finalMessage = formattedMessage.str();
    
    if (m_consoleOutput) {
        writeToConsole(level, finalMessage);
    }
    
    if (m_fileOutput) {
        writeToFile(finalMessage);
    }
}

void Logger::log(LogLevel level, const char* format, ...) {
    if (level < m_logLevel) return;
    
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    log(level, std::string(buffer));
}

void Logger::trace(const std::string& message) {
    log(LogLevel::LTrace, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::LDebug, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::LInfo, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::LWarning, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::LError, message);
}

void Logger::fatal(const std::string& message) {
    log(LogLevel::LFatal, message);
}

} // namespace CitySim