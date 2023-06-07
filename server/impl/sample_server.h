//#include <capnp/ez-rpc.h>

#include "rpc_event.h"
#include "custom-rpc.h"

/**
 *  @class SampleServer
 *  @brief This class provides interfaces to communicate with client.
 */
class SampleServer : public Server2ClientEvent {
 public:
  /**
   * @fn SampleServer
   * @brief Constructor
   */
  SampleServer(std::string server_adder);

  /**
   * @fn start
   * @brief Start event loop for communication with client by current thread.
   */
  void start();

 public:
  /**
   * @fn push_message_request
   * @brief push `push_message` event to client.
   */
  virtual void push_message_request();

 private:
  // This instance provides all the IF of the event between server and client.
  kj::Own<RPCEvent> m_RPCEventImpl;

  // This insance provides RPC logic like event-loop, wait-scope, ...etc.
  kj::Own<custom_rpc::CustomRpcServer> m_RPCLogicImpl;

  // This instance supports async execution on the main thread.
  kj::Maybe<const kj::Executor &> m_AsyncExecutor;
};