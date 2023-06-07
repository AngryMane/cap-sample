#include "sample_client.h"
#include "custom-rpc.h"
#include <thread>
#include <numeric>
#include <atomic>

const static std::vector<int> TARGET_SIGNALS = {
  SIGINT,
  SIGILL,
  SIGABRT,
  SIGFPE,
  SIGSEGV,
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
  std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
  return kj::READY_NOW;
}

SampleClient::SampleClient()
    : m_IsRunning(false),
      m_SendRPC(kj::heap<custom_rpc::CustomRpcClient>("unix:sample.sock")),
      m_SubscriberLifeCycle(),
      m_SubscriberImpl(
          Sample::Subscriber::Client(kj::heap<Server2ClientEvent>())){
}

 SampleClient::~SampleClient(){
  m_ReceiveThread.detach();
 }

void SampleClient::start() { 
  m_ReceiveThread = std::thread([&]() {
    m_IsRunning = true;
    this->m_ReceiveRPC = kj::heap<custom_rpc::CustomRpcClient>("unix:sample.sock");
    subscribe();

    for (auto signal : TARGET_SIGNALS){
      kj::UnixEventPort::captureSignal(signal);
    }
    kj::Promise<siginfo_t> never_done_casted = kj::NEVER_DONE;
    kj::Promise<siginfo_t> on_signal = std::accumulate(TARGET_SIGNALS.begin(), TARGET_SIGNALS.end(), kj::mv(never_done_casted), [&](kj::Promise<siginfo_t>& _on_signal, int signal){
      return _on_signal.exclusiveJoin(m_ReceiveRPC->getUnixEventPort().onSignal(signal));
    }).then([](siginfo_t a){
      std::cout << a.si_signo << std::endl;
      return a;
    });
    on_signal.wait(m_ReceiveRPC->getWaitScope());
    m_IsRunning = false;
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

bool SampleClient::is_running(){
  return m_IsRunning;
}