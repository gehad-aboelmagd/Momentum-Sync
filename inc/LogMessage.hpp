#pragma once

#include <string>
#include <cstdint>
#include <ctime>

typedef enum 
{
    INFO = 25,
    WARNING = 50,
    CRITICAL = 75,
}Severity;

class LogMessage
{
private:
    std::string app_name;
    std::string context;
    uint8_t value;
    std::string severity;
    std::string time_stamp;
public:
    LogMessage(std::string app_name, std::string context, uint8_t value);
    friend std::ostream &operator <<(std::ostream &outstream, const LogMessage &msg);
};