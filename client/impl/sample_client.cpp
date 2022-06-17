#include "sample_client.h"

kj::Promise<void> SampleClient::Server2ClientEvent::pushMessage(PushMessageContext context) {
    std::cout << __func__ << " called" << std::endl;
    return kj::READY_NOW;
}

SampleClient::SampleClient()
: m_RPCImpl(kj::heap<capnp::EzRpcClient>("unix:"))
, m_SubscriberImpl(Sample::Subscriber::Client(kj::heap<Server2ClientEvent>()))
, m_AsyncExecutor(kj::getCurrentThreadExecutor()){
    subscribe();
}

void SampleClient::start(){
    kj::NEVER_DONE.wait(m_RPCImpl->getWaitScope());
}

void SampleClient::initialize(){
    std::cout << __func__ <<  " called" << std::endl;

    KJ_IF_MAYBE(val, m_AsyncExecutor){
        if (val->isLive() == false){
            std::cout << "executor does not live" << std::endl;
            return;
        }
        val->executeSync([&](){
            auto& waitScope = m_RPCImpl->getWaitScope();
            auto sample_top = m_RPCImpl->getMain<Sample>();
            auto req = sample_top.initializeRequest();
            auto ack = req.send();
            auto ret = ack.eagerlyEvaluate(nullptr);
            });
    }

}

void SampleClient::subscribe(){
    std::cout << __func__ <<  " called" << std::endl;

    auto& waitScope = m_RPCImpl->getWaitScope();
    auto sample_top = m_RPCImpl->getMain<Sample>();
    auto subscribe_request = sample_top.subscribeRequest();
    subscribe_request.setSubscriber(m_SubscriberImpl);
    auto res = subscribe_request.send().wait(waitScope);
}