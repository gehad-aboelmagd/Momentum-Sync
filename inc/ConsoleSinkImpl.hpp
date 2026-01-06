#pragma once

#include <ostream>
#include "ILogSink.hpp"

class ConsoleSinkImpl: public ILogSink
{
private:
    std::ostream &my_ostream;
public:
    ConsoleSinkImpl(std::ostream &out_stream);
    void write(LogMessage &msg) override;
};