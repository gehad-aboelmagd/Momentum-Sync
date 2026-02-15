#include "LogManager.hpp"

LogManager::LogManager(int sink_num): log_sink(sink_num) {}

void LogManager::addSink(std::unique_ptr<ILogSink> sink)
{
    if(sink != nullptr)
    {
        log_sink.tryPush(std::move(sink));
    }
}

void LogManager::writeToAll(LogMessage &msg)
{
    for(int i=0; i<log_sink.getSize(); i++)
    {
        if(log_sink[i].has_value())
        {
            log_sink[i].value()->write(msg);
        }
        else
        {
            break;
        }
    }
}