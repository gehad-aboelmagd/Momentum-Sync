#ifndef LOG_MESSAGE_HPP_
#define LOG_MESSAGE_HPP_

#include <string>
#include <cstdint>
#include <ctime>

class LogMessage
{
private:
    std::string app_name;
    std::string payload;
    std::string severity;
    std::string time_stamp;
public:
    LogMessage(std::string app_name, std::string payload, std::string severity, std::string time_stamp);
    friend std::ostream &operator <<(std::ostream &outstream, const LogMessage &msg);
};

#endif // LOG_MESSAGE_HPP_