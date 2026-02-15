#include "LogMessage.hpp"

LogMessage::LogMessage(std::string app_name, std::string payload, std::string severity, std::string time_stamp)
: app_name(app_name), payload(payload), severity(severity), time_stamp(time_stamp){}

std::ostream & operator <<(std::ostream &outstream, const LogMessage &msg)
{
    outstream << "[" + msg.time_stamp + "] ";
    outstream << "[" + msg.app_name + "] ";
    outstream << "[" + msg.payload + "] ";
    outstream << "[" + msg.severity + "]\n";

    return outstream;
}