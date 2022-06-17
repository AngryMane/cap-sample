#include <unistd.h>
#include <iostream>
#include "../../interface/sample.cap.h"

using Client2ServerEvent = Sample::Server;

/** 
 *  @class Server2ClientEvent
 *  @brief This class defines the event interface from server to client.
 *  @details All the interfaces defined at this class have to implement by both `RPCEvent` and `SampleServer`.
 */
class Server2ClientEvent{

public:

    /**
     * @fn push_message_request
     * @brief This is pure virtual push_message event interface.
     */
    virtual void push_message_request() = 0;

};

/** 
 *  @class RPCEvent
 *  @brief This class defines the event interface from server to client.
 */
class RPCEvent : public Client2ServerEvent, Server2ClientEvent, public kj::Refcounted{

public:
    /**
     * @fn RPCEvent
     * @brief Constructor
     */
    RPCEvent();

    /**
     * @fn initialize
     * @brief When the client calls `initialize`, then this function will be called.
     */
    kj::Promise<void> initialize(InitializeContext context);

    /**
     * @fn subscribe
     * @brief When client call `subscribe`, then this function will be called.
     */
    kj::Promise<void> subscribe(SubscribeContext context);

    /**
     * @fn push_message_request
     * @brief When the server wants to push back `push_message` to the client, call this function. 
     */
    virtual void push_message_request();

private:

    // These are the contact point with the clients when pushing back any events from the server.
    kj::Vector<Sample::Subscriber::Client> m_Subscribers;
};