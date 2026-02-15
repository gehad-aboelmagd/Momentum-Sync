#ifndef LOG_FORMATTER_HPP_
#define LOG_FORMATTER_HPP_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <optional>

#include "../inc/LogMessage.hpp"

enum class TelemetrySrc
{   
    CPU,
    GPU,
    RAM,
};

enum class SeverityLvl
{
    CRITICAL,
    WARNING,
    INFO,
};

template <typename T>
std::string getEnumName(T value);

template <>
std::string getEnumName(TelemetrySrc src)
{
    std::string name;

    switch (src)
    {
    case TelemetrySrc::CPU:
        name = "CPU";
        break;
    case TelemetrySrc::GPU:
        name =  "GPU";
        break;
    case TelemetrySrc::RAM:
        name = "RAM";
        break;
    default:
        break;
    }

    return name;
}


template <>
std::string getEnumName(SeverityLvl lvl)
{
    std::string name = "";

    switch (lvl)
    {
    case SeverityLvl::CRITICAL:
        name = "CRITICAL";
        break;
    case SeverityLvl::WARNING:
        name = "WARNING";
        break;
    case SeverityLvl::INFO:
        name = "INFO";
        break;
    default:
        break;
    }

    return name;
}

struct CpuPolicy 
{
    static constexpr TelemetrySrc context = TelemetrySrc::CPU;
    static constexpr std::string_view unit = "%";
    static constexpr float WARNING = 75.0f;
    static constexpr float CRITICAL = 90.0f;

    static constexpr SeverityLvl inferSeverity(float val) noexcept {
        return (val > CRITICAL) ? SeverityLvl::CRITICAL
            : (val > WARNING)  ? SeverityLvl::WARNING
            :                    SeverityLvl::INFO;
    }
};

struct GpuPolicy 
{
    static constexpr TelemetrySrc context = TelemetrySrc::GPU;
    static constexpr std::string_view unit = "%";
    static constexpr float WARNING = 65.0f;
    static constexpr float CRITICAL = 80.0f;

    static constexpr SeverityLvl inferSeverity(float val) noexcept {
        return (val > CRITICAL) ? SeverityLvl::CRITICAL
            : (val > WARNING)  ? SeverityLvl::WARNING
            :                    SeverityLvl::INFO;
    }
};

struct RamPolicy 
{
    static constexpr TelemetrySrc context = TelemetrySrc::RAM;
    static constexpr std::string_view unit = "%";
    static constexpr float WARNING = 70.0f;
    static constexpr float CRITICAL = 85.0f;

    static constexpr SeverityLvl inferSeverity(float val) noexcept {
        return (val > CRITICAL) ? SeverityLvl::CRITICAL
            : (val > WARNING)  ? SeverityLvl::WARNING
            :                    SeverityLvl::INFO;
    }
};

template <typename T>
class LogFormatter
{
public:
    std::string currentTimeStamp()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t temp = std::chrono::system_clock::to_time_t(now);
        std::string stamp = std::ctime(&temp);

        if(stamp.back() == '\n')
        {
            stamp.pop_back();
        }

        return stamp;
    }
    std::string msgDescription(float value)
    {
        std::ostringstream out;
        out << std::fixed << std::setprecision(2) << value;
        
        return 
            getEnumName(T::context) + 
            " load is " + 
            out.str() + 
            static_cast<std::string>(T::unit);
    }
    std::string inferSeverity(float value)
    {
        return getEnumName(T::inferSeverity(value));
    }
    std::optional<LogMessage> formatDataToLogMsg(std::string app_name, const std::string &raw)
    {
        float value;
        try
        {
            value = std::stof(raw);  
        }
        catch(...)
        {
            return std::nullopt;
        }

        return LogMessage {app_name, msgDescription(value), inferSeverity(value), currentTimeStamp()};
    }
};

#endif // LOG_FORMATTER_HPP_