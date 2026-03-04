#include <iostream>
#include "LogManager.hpp"
#include "LogFormatter.hpp"
#include "ConsoleSinkImpl.hpp"
#include "FileSinkImpl.hpp"
#include "FileTelemetrySourceImpl.hpp"
#include "SomeIPTelemetrySourceImpl.hpp"

class MyMomyntumSync
{
private:
    std::string src_path = "cpu_readings.txt";
    std::string logs_path = "logs.txt";
    LogManager manager;
    LogFormatter<CpuPolicy> formatter;
    std::optional<LogMessage>msg;
    std::string readings;
    FileTelemetrySourceImpl src_file;
    SomeIPTelemetrySourceImpl someip_src;
    std::thread someip_thread;

public:
    MyMomyntumSync(): manager(5), src_file(src_path)
    {
        manager.addSink(std::unique_ptr<ConsoleSinkImpl>(new ConsoleSinkImpl(std::cout)));
        manager.addSink(std::unique_ptr<FileSinkImpl>(new FileSinkImpl(logs_path)));

        src_file.openSource();
        someip_thread = std::thread([this]() {
        someip_src.openSource();
        });

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    void start()
    {
        for(int i=0; i<10; i++)
        {
            src_file.readSource(readings);   
            msg = formatter.formatDataToLogMsg("app0", readings);
            if(msg.has_value())
            {
                manager.writeToAll(msg.value());
            }

            someip_src.readSource(readings);
            msg = formatter.formatDataToLogMsg("app0", readings);
            if(msg.has_value())
            {
                manager.writeToAll(msg.value());
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        } 
    }

    ~MyMomyntumSync()
    {
        someip_thread.detach();
    }
};

int main()
{

    MyMomyntumSync myMomyntumSync;
    myMomyntumSync.start();
}