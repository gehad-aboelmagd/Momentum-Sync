#ifndef SOMEIP_TELEMETRY_SOURCE_IMPL_HPP_
#define SOMEIP_TELEMETRY_SOURCE_IMPL_HPP_

#include <memory>
#include "ITelemetrySource.hpp"
#include "SomeIPClient.hpp"

class SomeIPTelemetrySourceImpl: public ITelemetrySource
{
private:
    std::unique_ptr<SomeIPClient> client;
public:
    bool openSource() override;
    bool readSource(std::string &out) override;
};

#endif // SOMEIP_TELEMETRY_SOURCE_IMPL_HPP_