#ifndef FILE_TELEMETRY_SOURCE_IMPL_HPP_
#define FILE_TELEMETRY_SOURCE_IMPL_HPP_

#include <memory>
#include "SafeFile.hpp"
#include "ITelemetrySource.hpp"

class FileTelemetrySourceImpl: public ITelemetrySource
{
private:
    std::unique_ptr<SafeFile> file = nullptr;
public:
    bool openSource(std::string &path) override;
    bool readSource(std::string &out) override;
};

#endif // FILE_TELEMETRY_SOURCE_IMPL_HPP_