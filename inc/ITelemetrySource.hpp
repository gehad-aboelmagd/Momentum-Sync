#include <string>

class ITelemetrySource
{
private:
public:
    virtual bool openSource(std::string &path) = 0;
    virtual bool readSource(std::string &out) = 0;
};