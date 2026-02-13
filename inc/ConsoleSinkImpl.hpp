#ifndef LOG_FORMATTER_HPP_
#define LOG_FORMATTER_HPP_

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

#endif // LOG_FORMATTER_HPP_