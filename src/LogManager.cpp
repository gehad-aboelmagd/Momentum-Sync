#include "LogManager.hpp"

void LogManager::addSink(std::unique_ptr<ILogSink> sink)
{
    if(sink != nullptr)
    {
        log_sink.push_back(std::move(sink));
    }
}

void LogManager::writeToAll(LogMessage &msg)
{
    for(auto &sink: log_sink)
    {
        sink->write(msg);
    }
}