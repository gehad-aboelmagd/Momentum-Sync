#ifndef ITELEMETRY_SOURCE_HPP_
#define ITELEMETRY_SOURCE_HPP_

#include <string>

class ITelemetrySource
{
private:
public:
    virtual bool openSource(std::string &path) = 0;
    virtual bool readSource(std::string &out) = 0;
};

#endif // ITELEMETRY_SOURCE_HPP_