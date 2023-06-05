#include "sample_client.h"
#include <thread>

kj::Promise<void> SampleClient::Server2ClientEvent::pushMessage(
    PushMessageContext context) {
  std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
  return kj::READY_NOW;
}

SampleClient::SampleClient()
    : m_SendRPC(kj::heap<capnp::EzRpcClient>("unix:sample.sock")),
      m_SubscriberLifeCycle(),
      m_SubscriberImpl(
          Sample::Subscriber::Client(kj::heap<Server2ClientEvent>())){
}

 SampleClient::~SampleClient(){
  m_ReceiveThread.detach();
 }

void SampleClient::start() { 
  m_ReceiveThread = std::thread([&]() {
    this->m_ReceiveRPC = kj::heap<capnp::EzRpcClient>("unix:sample.sock");
    subscribe();
    kj::NEVER_DONE.wait(m_ReceiveRPC->getWaitScope()); 
  });
}

void SampleClient::initialize() {
  std::cout << __PRETTY_FUNCTION__  << " called" << std::endl;

  auto& waitScope = m_SendRPC->getWaitScope();
  auto sample_top = m_SendRPC->getMain<Sample>();
  auto req = sample_top.initializeRequest();
  auto ack = req.send();
  auto ret = ack.eagerlyEvaluate(nullptr);
}

void SampleClient::subscribe() {
  std::cout << __PRETTY_FUNCTION__  << " called" << std::endl;

  auto& waitScope = m_ReceiveRPC->getWaitScope();
  auto sample_top = m_ReceiveRPC->getMain<Sample>();
  auto subscribe_request = sample_top.subscribeRequest();
  subscribe_request.setSubscriber(m_SubscriberImpl);
  m_SubscriberLifeCycle.push_back(subscribe_request.send().wait(waitScope));
}