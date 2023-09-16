#include "rpc_event.h"

RPCEvent::RPCEvent() : m_Subscribers() {}

kj::Promise<void> RPCEvent::initialize(InitializeContext context) {
  std::cout << "[SERVER]" << __PRETTY_FUNCTION__  << " called" << std::endl;
  return kj::READY_NOW;
}

kj::Promise<void> RPCEvent::subscribe(SubscribeContext context) {
  std::cout << "[SERVER]" << __PRETTY_FUNCTION__  << " called" << std::endl;
  try {
    auto subscriber = context.getParams().getSubscriber();
    m_Subscribers.add(subscriber);
  } catch (kj::Exception e) {
    std::cout << e.getDescription().cStr() << std::endl;
  }

  return kj::READY_NOW;
}

void RPCEvent::push_message_request() {
  std::cout << "[SERVER]" << __PRETTY_FUNCTION__  << " called" << std::endl;

  // If called before running PRC server, m_RPCEventHandler has no subscribers.
  // So It's unnecessary to check running.
  for (auto subscriber : m_Subscribers) {
    std::cout << "[SERVER]" << __PRETTY_FUNCTION__  << " called a subscriber" << std::endl;
    auto request = subscriber.pushMessageRequest();
    auto result = request.send();
  }
}
