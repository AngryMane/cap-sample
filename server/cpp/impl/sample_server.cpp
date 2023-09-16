#include "sample_server.h"
#include <numeric>
#include <vector>

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
  // When client had gone. Cap'n Proto masks SIGPIPE, so nothing to do here. 
  //SIGPIPE,  
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

SampleServer::SampleServer()
  : m_RPCEventImpl(kj::refcounted<RPCEvent>()),
    m_AsynIoContext(kj::setupAsyncIo()){
  for (auto signal : TARGET_SIGNALS){
    kj::UnixEventPort::captureSignal(signal);
  }
}

void SampleServer::start(std::string server_adder) {
  capnp::TwoPartyServer server(kj::addRef(*m_RPCEventImpl));
  m_AsyncExecutor = kj::getCurrentThreadExecutor();
  auto address = m_AsynIoContext.provider->getNetwork().parseAddress(server_adder).wait(m_AsynIoContext.waitScope);
  auto listener = address->listen();
  auto listenPromise = server.listen(*listener);

  kj::Promise<siginfo_t> never_done_casted = listenPromise.then([](){return siginfo_t();});
  kj::Promise<siginfo_t> on_signal = std::accumulate(TARGET_SIGNALS.begin(), TARGET_SIGNALS.end(), kj::mv(never_done_casted), [&](kj::Promise<siginfo_t>& _on_signal, int signal){
    return _on_signal.exclusiveJoin(m_AsynIoContext.unixEventPort.onSignal(signal));
  }).then([](siginfo_t a){
    std::cout << a.si_signo << std::endl;
    return a;
  });
  on_signal.wait(m_AsynIoContext.waitScope);
}

void SampleServer::taskFailed(kj::Exception&& exception){
    kj::throwFatalException(kj::mv(exception));
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
