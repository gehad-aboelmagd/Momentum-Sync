#include <iostream>
#include "ConsoleSinkImpl.hpp"

ConsoleSinkImpl::ConsoleSinkImpl(std::ostream &out_stream)
: my_ostream(out_stream)
{

}

void ConsoleSinkImpl::write(LogMessage &msg)
{
    my_ostream << msg;
}