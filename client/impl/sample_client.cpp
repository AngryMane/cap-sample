#include "sample_client.h"
#include <thread>
#include <numeric>
#include <atomic>

#include <kj/async-io.h>
#include <kj/async-unix.h>
#include <capnp/rpc-twoparty.h>

const static std::vector<int> TARGET_SIGNALS = {
  SIGINT,
  //SIGILL,
  SIGABRT,
  //SIGFPE,
  //SIGSEGV,
  SIGTERM,
  SIGHUP,
  SIGQUIT,
  //SIGTRAP,
  //SIGKILL,
  SIGPIPE,
  //SIGALRM,
  //SIGURG,
  //SIGSTOP,
  //SIGTSTP,
  //SIGCONT,
  //SIGCHLD,
  //,
  //SIGTTIN,
  //SIGTTOU,
  //SIGPOLL,
  SIGXFSZ,
  SIGXCPU,
  //SIGVTALRM,
  //SIGPROF,
};

kj::Promise<void> SampleClient::Server2ClientEvent::pushMessage(
    PushMessageContext context) {
  std::cout << "[CLIENT]" << __PRETTY_FUNCTION__ << " called" << std::endl;
  return kj::READY_NOW;
}

SampleClient::SampleClient()
    : m_IsRunning(false),
      m_SendAsyncIoContext(kj::setupAsyncIo()),
      m_SubscriberLifeCycle(),
      m_SubscriberImpl(
          Sample::Subscriber::Client(kj::heap<Server2ClientEvent>())){
  m_Address = m_SendAsyncIoContext.provider->getNetwork()
      .parseAddress("unix:sample.sock").wait(m_SendAsyncIoContext.waitScope);
  m_Connection = m_Address->connect().wait(m_SendAsyncIoContext.waitScope);
  m_SendRPC = kj::heap<capnp::TwoPartyClient>(*m_Connection);

  // WARNING: This must run on the main thread.
  sigset_t mask;
  sigemptyset(&mask);
  for (auto i : TARGET_SIGNALS){
    sigaddset(&mask, i);
  }
  pthread_sigmask(SIG_BLOCK, &mask, nullptr);
}

SampleClient::~SampleClient(){
  std::cout << "[CLIENT]" << __PRETTY_FUNCTION__ << " called" << std::endl;
  if (m_ReceiveThread.joinable()) {
    m_ReceiveThread.detach();
  }
}

void SampleClient::start() { 
  m_ReceiveThread = std::thread([&]() {
    m_IsRunning = true;
    auto async_io = kj::setupAsyncIo();
    auto address = async_io.provider->getNetwork()
      .parseAddress("unix:sample.sock").wait(async_io.waitScope);
    auto connection = address->connect().wait(async_io.waitScope);
    kj::Own<capnp::TwoPartyClient> rpc_client = kj::heap<capnp::TwoPartyClient>(*connection);
    subscribe(async_io, rpc_client);

    for (auto signal : TARGET_SIGNALS){
      kj::UnixEventPort::captureSignal(signal);
    }

    kj::Promise<siginfo_t> never_done_casted = kj::NEVER_DONE;
    kj::Promise<siginfo_t> on_signal = std::accumulate(TARGET_SIGNALS.begin(), TARGET_SIGNALS.end(), kj::mv(never_done_casted), [&](kj::Promise<siginfo_t>& _on_signal, int signal){
      return _on_signal.exclusiveJoin(async_io.unixEventPort.onSignal(signal));
    }).then([](siginfo_t a){
      std::cout << a.si_signo << std::endl;
      return a;
    });
    on_signal.wait(async_io.waitScope);
    m_IsRunning = false;
    m_Connection.~Own();
    m_Address.~Own();
  });
}

void SampleClient::initialize() {
  std::cout << "[CLIENT]" << __PRETTY_FUNCTION__  << " called" << std::endl;
  auto cap = m_SendRPC->bootstrap().castAs<Sample>();
  auto req = cap.initializeRequest();
  auto ret = req.send().wait(m_SendAsyncIoContext.waitScope);
}

void SampleClient::subscribe(kj::AsyncIoContext& async_io, kj::Own<capnp::TwoPartyClient>& rpc_client) {
  std::cout << "[CLIENT]" << __PRETTY_FUNCTION__  << " called" << std::endl;
  auto cap = rpc_client->bootstrap().castAs<Sample>();
  auto subscribe_request = cap.subscribeRequest();
  subscribe_request.setSubscriber(m_SubscriberImpl);
  m_SubscriberLifeCycle.push_back(subscribe_request.send().wait(async_io.waitScope));
}

bool SampleClient::is_running(){
  return m_IsRunning;
}
