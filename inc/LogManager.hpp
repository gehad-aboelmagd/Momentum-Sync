#ifndef LOG_MANAGER_HPP_
#define LOG_MANAGER_HPP_

#include <memory>
#include "RingBuffer.hpp"
#include "LogMessage.hpp"
#include "ILogSink.hpp"

class LogManager
{
private:
    RingBuffer<std::unique_ptr<ILogSink>> log_sink;
public:
    LogManager(int sink_num);
    void addSink(std::unique_ptr<ILogSink> sink);
    void writeToAll(LogMessage &msg);
};

#endif // LOG_MANAGER_HPP_