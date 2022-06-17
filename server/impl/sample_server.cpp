#include "sample_server.h"

SampleServer::SampleServer(std::string server_adder)
    : m_RPCEventImpl(kj::refcounted<RPCEvent>())
    , m_RPCLogicImpl(kj::heap<capnp::EzRpcServer>(kj::addRef(*m_RPCEventImpl), server_adder))
    , m_AsyncExecutor(kj::getCurrentThreadExecutor()) {
}


void SampleServer::start() {
    auto& wait_scope = m_RPCLogicImpl->getWaitScope();
    kj::NEVER_DONE.wait(wait_scope);
}

void SampleServer::push_message_request(){
    KJ_IF_MAYBE(val, m_AsyncExecutor){
        if (val->isLive() == false){
            std::cout << "executor does not live" << std::endl;
            return;
        }
        val->executeSync([&](){m_RPCEventImpl->push_message_request();});
    }
}