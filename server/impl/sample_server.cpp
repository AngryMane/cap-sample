#include "sample_server.h"
#include <numeric>
#include <vector>

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

SampleServer::SampleServer(std::string server_adder)
  : m_RPCEventImpl(kj::refcounted<RPCEvent>()),
    m_RPCLogicImpl(kj::heap<custom_rpc::CustomRpcServer>(kj::addRef(*m_RPCEventImpl),
                                                server_adder)),
    m_AsyncExecutor(kj::getCurrentThreadExecutor()) {
  for (auto signal : TARGET_SIGNALS){
    kj::UnixEventPort::captureSignal(signal);
  }
}

void SampleServer::start() {
  auto& wait_scope = m_RPCLogicImpl->getWaitScope();
  kj::Promise<siginfo_t> never_done_casted = kj::NEVER_DONE;
  kj::Promise<siginfo_t> on_signal = std::accumulate(TARGET_SIGNALS.begin(), TARGET_SIGNALS.end(), kj::mv(never_done_casted), [&](kj::Promise<siginfo_t>& _on_signal, int signal){
    return _on_signal.exclusiveJoin(m_RPCLogicImpl->getUnixEventPort().onSignal(signal));
  }).then([](siginfo_t a){
    std::cout << a.si_signo << std::endl;
    return a;
  });
  on_signal.wait(wait_scope);
}

void SampleServer::push_message_request() {
  KJ_IF_MAYBE(val, m_AsyncExecutor) {
    if (val->isLive() == false) {
      std::cout << "executor does not live" << std::endl;
      return;
    }
    val->executeSync([&]() { m_RPCEventImpl->push_message_request(); });
  }
}