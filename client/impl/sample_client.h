#include <capnp/ez-rpc.h>
#include <unistd.h>

#include <iostream>

#include "../../interface/sample.cap.h"

/**
 *  @class SampleClient
 *  @brief This class provides the event interface from client to server, and
 * vise-versa.
 */
class SampleClient {
 private:
  /**
   *  @class Server2ClientEvent
   *  @brief This class defines the event interface from server to client.
   */
  class Server2ClientEvent : public Sample::Subscriber::Server {
   protected:
    /**
     * @fn pushMessage
     * @brief When the server pushes back `pushMessage`, then this function will
     * be called.
     */
    kj::Promise<void> pushMessage(PushMessageContext context) override;
  };

 public:
  /**
   * @fn SampleClient
   * @brief Constructor
   */
  SampleClient();

  /**
   * @fn start
   * @brief Start event loop. This is a blocking function till the end of event
   * loop.
   */
  void start();

  /**
   * @fn initialize
   * @brief When requesting `initialize`, call this function.
   */
  void initialize();

  /**
   * @fn subscribe
   * @brief When requesting `subscribe`, call this function.
   */
  void subscribe();

 private:
  // This insance provides RPC logic like event-loop, wait-scope, ...etc.
  kj::Own<capnp::EzRpcClient> m_RPCImpl;

  // These are the contact point with the server when pushing back any events
  // from the server.
  Sample::Subscriber::Client m_SubscriberImpl;

  // This instance supports async execution on the main thread.
  kj::Maybe<const kj::Executor &> m_AsyncExecutor;
};