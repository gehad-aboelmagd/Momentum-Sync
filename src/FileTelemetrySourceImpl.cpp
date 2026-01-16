#include <memory>
#include "SafeFile.hpp"
#include "ITelemetrySource.hpp"

class FileTelemetrySourceImpl: public ITelemetrySource
{
private:
    std::unique_ptr<SafeFile> file = nullptr;
public:
    bool openSource(std::string &path) override
    {
        file.reset(new SafeFile(path));
        if(file->getState() == -1)
        {
            return false;
        }
        return true;
    }
    bool readSource(std::string &out) override
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
};