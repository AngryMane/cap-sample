//#include <capnp/ez-rpc.h>

#include "rpc_event.h"
#include <kj/async-io.h>

namespace kj {
  class ConnectionReceiver;
}

/**
 *  @class SampleServer
 *  @brief This class provides interfaces to communicate with client.
 */
class SampleServer :  public Server2ClientEvent {
 public:
  /**
   * @fn SampleServer
   * @brief Constructor
   */
  SampleServer();

  /**
   * @fn start
   * @brief Start event loop for communication with client by current thread.
   */
  void start(std::string server_adder);

public:

  /**
   * @fn start
   * @brief Start event loop for communication with client by current thread.
   */
  virtual void taskFailed(kj::Exception&& exception);

 public:
  /**
   * @fn push_message_request
   * @brief push `push_message` event to client.
   */
  virtual void push_message_request();

 private:

  // This instance provides all the IF of the event between server and client.
  kj::Own<RPCEvent> m_RPCEventImpl;

  // This instance supports async execution on the main thread.
  kj::Maybe<const kj::Executor &> m_AsyncExecutor;

  // 
  kj::AsyncIoContext m_AsynIoContext;
};
