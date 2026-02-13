#ifndef FILE_SINK_IMPL_HPP_
#define FILE_SINK_IMPL_HPP_

#include <fstream>
#include "ILogSink.hpp"

class FileSinkImpl: public ILogSink
{
private:
    std::ofstream my_ofstream;
public:
    FileSinkImpl(std::string &path);
    void write(LogMessage &msg) override;
};

#endif // FILE_SINK_IMPL_HPP_