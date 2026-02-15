#include "FileTelemetrySourceImpl.hpp"


bool FileTelemetrySourceImpl::openSource(std::string &path)
{
    file.reset(new SafeFile(path));
    if(file->getState() == -1)
    {
        return false;
    }
    return true;
}
bool FileTelemetrySourceImpl::readSource(std::string &out)
{
    if(file != nullptr && file->getState() != -1)
    {
        auto temp = file->readFile();
        if(temp.has_value())
        {
            out = temp.value();
            return true;
        }
        return false;
    }
    
    return false;
}