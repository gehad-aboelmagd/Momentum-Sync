#include <iostream>
#include <stdexcept>
#include <fcntl.h>

#include "FileSinkImpl.hpp"

FileSinkImpl::FileSinkImpl(std::string &path)
{
    my_ofstream.open(path);
    if(!my_ofstream.is_open())
    {
        std::cerr <<"Error opening the file\n";
        std::cerr << "You may check your file path or permissions\n";
    }
}

void FileSinkImpl::write(LogMessage &msg)
{
    my_ofstream << msg;
}

FileSinkImpl::~FileSinkImpl()
{
    my_ofstream.close();
}