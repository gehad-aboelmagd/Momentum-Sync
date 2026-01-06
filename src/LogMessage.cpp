#include "LogMessage.hpp"

LogMessage::LogMessage(std::string app_name, std::string context, uint8_t value)
: app_name(app_name), context(context), value(value)
{
    if(value <= INFO)
    {
        this->severity = "INFO";
    }
    else if(value <= WARNING)
    {
        this->severity = "WARNING";
    }
    else if(value <= CRITICAL)
    {
        this->severity = "CRITICAL";
    }
    
    time_t current_time = time(nullptr);
    this->time_stamp = ctime(&current_time);
    this->time_stamp.pop_back();
}

std::ostream & operator <<(std::ostream &outstream, const LogMessage &msg)
{
    outstream << "[" + msg.time_stamp + "] ";
    outstream << "[" + msg.app_name + "] ";
    outstream << "[" + msg.context + "] ";
    outstream << "[" + std::to_string(msg.value) + "%] ";
    outstream << "[" + msg.severity + "]\n";

    return outstream;
}