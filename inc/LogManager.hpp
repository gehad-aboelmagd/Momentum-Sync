#pragma once

#include <vector>
#include <memory>
#include "LogMessage.hpp"
#include "ILogSink.hpp"

class LogManager
{
private:
    std::vector<std::unique_ptr<ILogSink>> log_sink;
public:
    void addSink(std::unique_ptr<ILogSink> sink);
    void writeToAll(LogMessage &msg);
};