#ifndef ILOG_SINK_HPP_
#define ILOG_SINK_HPP_

#include "LogMessage.hpp"

class ILogSink
{    
public:
    virtual void write(LogMessage &msg) = 0;
    virtual ~ILogSink() = default;
};

#endif // ILOG_SINK_HPP_