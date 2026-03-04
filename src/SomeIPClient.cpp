#include "SomeIPClient.hpp"

SomeIPClient::SomeIPClient()
{
    runtime_ = vsomeip::runtime::get();
    if(!runtime_)
    {
        throw std::runtime_error("Unable to create a vsomeip runtime\n");
    }
    app_ = runtime_->create_application("ClientApp");
    if(!app_)
    {
        throw std::runtime_error("Unable to create a vsomeip application\n");
    }
    if(!app_->init())
    {
        throw std::runtime_error("Unable to initialize application\n");
    }
    app_->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID, 
        [this](const std::shared_ptr<vsomeip::message> &response)
        {
            this->on_message(response);
        }
    );
    app_->register_availability_handler(SERVICE_ID, INSTANCE_ID, 
        [this](vsomeip::service_t service, vsomeip::instance_t instance, bool available)
        {
            std::cout << "availability changed\n";
            if(available)
            {
                std::cout << "Service is available now\n";
                condition_.notify_one();
            }
        }            
    );
    app_->request_service(SERVICE_ID, INSTANCE_ID);
    request_thread_ = std::thread(&SomeIPClient::send_request, this);
}

void SomeIPClient::start()
{
    app_->start();
}

void SomeIPClient::send_request()
{
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock);

    std::shared_ptr <vsomeip::message> request = runtime_->create_request();
    request->set_service(SERVICE_ID);
    request->set_instance(INSTANCE_ID);
    request->set_method(METHOD_ID);

    app_->send(request);
}

void SomeIPClient::on_message(const std::shared_ptr<vsomeip::message> &response)
{
    std::shared_ptr<vsomeip::payload> payload = response->get_payload();
    if(!payload)
    {
        throw std::runtime_error("Got a null payload\n");
    }
    vsomeip::length_t length = payload->get_length();
    if(!length)
    {
        throw std::runtime_error("Got an empty payload\n");
    }

    load_percentage_ = *(payload->get_data());
    std::cout << "Received load: " << static_cast<int>(load_percentage_)<< std::endl;
}

SomeIPClient::~SomeIPClient()
{
    if(app_)
    {
        // if(request_thread_.joinable())
        // {
        //     request_thread_.join();
        // }
        app_->stop();
    }
}
