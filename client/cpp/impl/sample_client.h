#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>
#include <capnp/rpc-twoparty.h>

#include "sample.cap.h"

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
   * @fn ~SampleClient
   * @brief Destructor
   */
  ~SampleClient();

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
  void subscribe(kj::AsyncIoContext& async_io, kj::Own<capnp::TwoPartyClient>& rpc_client);

  /**
   * @fn is_running
   * @brief is running or not
   */
  bool is_running();

 private:
  bool m_IsRunning; 

  std::thread m_ReceiveThread;

  kj::Own<kj::NetworkAddress> m_Address;

  kj::Own<kj::AsyncIoStream> m_Connection;

  // This insance provides RPC logic like event-loop, wait-scope, ...etc.
  kj::AsyncIoContext m_SendAsyncIoContext;

  // This insance provides RPC logic like event-loop, wait-scope, ...etc.
  kj::Own<capnp::TwoPartyClient> m_SendRPC;

  // This insance provides RPC logic like event-loop, wait-scope, ...etc.
  kj::Own<capnp::TwoPartyClient> m_ReceiveRPC;

  // These are the contact point with the server when pushing back any events
  // from the server.
  Sample::Subscriber::Client m_SubscriberImpl;

  // This keeps the response instance of the subscribe requests.
  // kj Server can't call back subscriber when the client app releases the responses in this.
  std::vector<capnp::Response<Sample::SubscribeResults>> m_SubscriberLifeCycle;
};
