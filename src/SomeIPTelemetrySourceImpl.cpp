#include "SomeIPTelemetrySourceImpl.hpp"

bool SomeIPTelemetrySourceImpl::openSource()
{
    client = std::make_unique<SomeIPClient>();
    client->start();
    return true;
}

bool SomeIPTelemetrySourceImpl::readSource(std::string &out)
{
    out = client->get_load_percentage();
    return true;
}