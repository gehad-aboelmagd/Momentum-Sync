#ifndef SOMEIP_CLIENT_HPP_
#define SOMEIP_CLIENT_HPP_

#include <iostream>
#include <stdexcept>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "vsomeip/vsomeip.hpp"

#define SERVICE_ID  0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID   0x0421


class SomeIPClient
{
private:
    std::shared_ptr<vsomeip::runtime> runtime_;
    std::shared_ptr<vsomeip::application> app_;
    std::atomic<vsomeip::byte_t> load_percentage_ {0};
    std::mutex mutex_;
    std::condition_variable condition_;
    std::thread request_thread_;
public:
    SomeIPClient();

    void start();

    void send_request();

    void on_message(const std::shared_ptr<vsomeip::message> &response);

    std::string get_load_percentage();

    ~SomeIPClient();
};

#endif // SOMEIP_CLIENT_HPP_