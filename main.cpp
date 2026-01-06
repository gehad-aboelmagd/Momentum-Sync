#include <iostream>
#include "LogManager.hpp"
#include "ConsoleSinkImpl.hpp"
#include "FileSinkImpl.hpp"

int main()
{
    LogManager manager;
    manager.addSink(std::unique_ptr<ConsoleSinkImpl>(new ConsoleSinkImpl(std::cout)));

    std::string path = "logs.txt";
    manager.addSink(std::unique_ptr<FileSinkImpl>(new FileSinkImpl(path)));

    LogMessage msg("App0", "CPU", 20);
    manager.writeToAll(msg);
}