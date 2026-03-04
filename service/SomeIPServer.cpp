#include <iostream>
#include <stdexcept>
#include <atomic>
#include "vsomeip/vsomeip.hpp"

#define SERVICE_ID  0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID   0x0421

class SomeIPServer
{
private:
    std::shared_ptr<vsomeip::runtime> runtime_;
    std::shared_ptr <vsomeip::application> app_;
    std::atomic <vsomeip::byte_t> percentage_load {12}; 
public:
    SomeIPServer()
    {
        runtime_ = vsomeip::runtime::get();
        if(!runtime_)
        {
            throw std::runtime_error("Unable to create vsomeip runtime\n");
        }
        app_ = runtime_->create_application("ServerApp");
        if(!app_)
        {
            throw std::runtime_error("Unable to create vsomeip application\n");
        }
        if(!app_->init())
        {
            throw std::runtime_error("Unable to initialize applciation\n");
        }
        app_->register_message_handler( SERVICE_ID, INSTANCE_ID, METHOD_ID, 
            [this](const std::shared_ptr<vsomeip::message> &request){
                this->on_message(request);
            }
        );
        app_->offer_service(SERVICE_ID, INSTANCE_ID);
    }

    void start()
    {
        app_->start();
    }

    void on_message(const std::shared_ptr<vsomeip::message> &request)
    {
        std::vector<vsomeip::byte_t> data{percentage_load};
        std::shared_ptr<vsomeip::payload> payload = runtime_->create_payload(data);
        
        std::shared_ptr<vsomeip::message> response = runtime_->create_response(request);
        response->set_payload(payload);

        std::cout << "server sending request: " << request->get_payload()->get_data() << "\n\n\n";
        app_->send(response);
    }

    ~SomeIPServer()
    {
        if(app_)
        {
            app_->stop();
        }
    }
};

int main()
{
    SomeIPServer server;
    server.start();
}