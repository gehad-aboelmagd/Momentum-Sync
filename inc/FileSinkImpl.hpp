#pragma once

#include <fstream>
#include "ILogSink.hpp"

class FileSinkImpl: public ILogSink
{
private:
    std::ofstream my_ofstream;
public:
    FileSinkImpl(std::string &path);
    void write(LogMessage &msg) override;
    ~FileSinkImpl() override;
};