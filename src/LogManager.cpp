#include "LogManager.hpp"
#include "ThreadPool.hpp"

LogManager::LogManager(int sink_num)
: log_sink(sink_num) 
{
    
}

void LogManager::addSink(std::unique_ptr<ILogSink> sink)
{
    if(sink != nullptr)
    {
        log_sink.tryPush(std::move(sink));
    }
}

void LogManager::writeToAll(LogMessage &msg)
{
    ThreadPool pool(log_sink.getSize());
    for(int i=0; i<log_sink.getSize(); i++)
    {
        if(log_sink[i].has_value())
        {
            pool.producer(
                [this, i, &msg](){
                    log_sink[i].value()->write(msg);
                }
            );
        }      
    }
}