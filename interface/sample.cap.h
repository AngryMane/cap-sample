// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: sample.cap

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>
#if !CAPNP_LITE
#include <capnp/capability.h>
#endif  // !CAPNP_LITE

#if CAPNP_VERSION != 9001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(da55b331806ed8e2);
CAPNP_DECLARE_SCHEMA(f0699e6953a549f3);
CAPNP_DECLARE_SCHEMA(de00b8bb167ebe4b);
CAPNP_DECLARE_SCHEMA(92eaa7183bd6bfdb);
CAPNP_DECLARE_SCHEMA(a281da8ba4f2ddcd);
CAPNP_DECLARE_SCHEMA(fff805819910da1f);
CAPNP_DECLARE_SCHEMA(c278bf4467bea2a5);
CAPNP_DECLARE_SCHEMA(cbe193bf50c90056);

}  // namespace schemas
}  // namespace capnp


struct Sample {
  Sample() = delete;

#if !CAPNP_LITE
  class Client;
  class Server;
#endif  // !CAPNP_LITE

  struct Subscriber;
  struct InitializeParams;
  struct InitializeResults;
  struct SubscribeParams;
  struct SubscribeResults;

  #if !CAPNP_LITE
  struct _capnpPrivate {
    CAPNP_DECLARE_INTERFACE_HEADER(da55b331806ed8e2)
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
  };
  #endif  // !CAPNP_LITE
};

struct Sample::Subscriber {
  Subscriber() = delete;

#if !CAPNP_LITE
  class Client;
  class Server;
#endif  // !CAPNP_LITE

  struct PushMessageParams;
  struct PushMessageResults;

  #if !CAPNP_LITE
  struct _capnpPrivate {
    CAPNP_DECLARE_INTERFACE_HEADER(f0699e6953a549f3)
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
  };
  #endif  // !CAPNP_LITE
};

struct Sample::Subscriber::PushMessageParams {
  PushMessageParams() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(de00b8bb167ebe4b, 0, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Sample::Subscriber::PushMessageResults {
  PushMessageResults() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(92eaa7183bd6bfdb, 1, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Sample::InitializeParams {
  InitializeParams() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(a281da8ba4f2ddcd, 0, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Sample::InitializeResults {
  InitializeResults() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(fff805819910da1f, 1, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Sample::SubscribeParams {
  SubscribeParams() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(c278bf4467bea2a5, 0, 1)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Sample::SubscribeResults {
  SubscribeResults() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(cbe193bf50c90056, 1, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

#if !CAPNP_LITE
class Sample::Client
    : public virtual ::capnp::Capability::Client {
public:
  typedef Sample Calls;
  typedef Sample Reads;

  Client(decltype(nullptr));
  explicit Client(::kj::Own< ::capnp::ClientHook>&& hook);
  template <typename _t, typename = ::kj::EnableIf< ::kj::canConvert<_t*, Server*>()>>
  Client(::kj::Own<_t>&& server);
  template <typename _t, typename = ::kj::EnableIf< ::kj::canConvert<_t*, Client*>()>>
  Client(::kj::Promise<_t>&& promise);
  Client(::kj::Exception&& exception);
  Client(Client&) = default;
  Client(Client&&) = default;
  Client& operator=(Client& other);
  Client& operator=(Client&& other);

  ::capnp::Request< ::Sample::InitializeParams,  ::Sample::InitializeResults> initializeRequest(
      ::kj::Maybe< ::capnp::MessageSize> sizeHint = nullptr);
  ::capnp::Request< ::Sample::SubscribeParams,  ::Sample::SubscribeResults> subscribeRequest(
      ::kj::Maybe< ::capnp::MessageSize> sizeHint = nullptr);

protected:
  Client() = default;
};

class Sample::Server
    : public virtual ::capnp::Capability::Server {
public:
  typedef Sample Serves;

  ::capnp::Capability::Server::DispatchCallResult dispatchCall(
      uint64_t interfaceId, uint16_t methodId,
      ::capnp::CallContext< ::capnp::AnyPointer, ::capnp::AnyPointer> context)
      override;

protected:
  typedef  ::Sample::InitializeParams InitializeParams;
  typedef  ::Sample::InitializeResults InitializeResults;
  typedef ::capnp::CallContext<InitializeParams, InitializeResults> InitializeContext;
  virtual ::kj::Promise<void> initialize(InitializeContext context);
  typedef  ::Sample::SubscribeParams SubscribeParams;
  typedef  ::Sample::SubscribeResults SubscribeResults;
  typedef ::capnp::CallContext<SubscribeParams, SubscribeResults> SubscribeContext;
  virtual ::kj::Promise<void> subscribe(SubscribeContext context);

  inline  ::Sample::Client thisCap() {
    return ::capnp::Capability::Server::thisCap()
        .template castAs< ::Sample>();
  }

  ::capnp::Capability::Server::DispatchCallResult dispatchCallInternal(
      uint16_t methodId,
      ::capnp::CallContext< ::capnp::AnyPointer, ::capnp::AnyPointer> context);
};
#endif  // !CAPNP_LITE

#if !CAPNP_LITE
class Sample::Subscriber::Client
    : public virtual ::capnp::Capability::Client {
public:
  typedef Subscriber Calls;
  typedef Subscriber Reads;

  Client(decltype(nullptr));
  explicit Client(::kj::Own< ::capnp::ClientHook>&& hook);
  template <typename _t, typename = ::kj::EnableIf< ::kj::canConvert<_t*, Server*>()>>
  Client(::kj::Own<_t>&& server);
  template <typename _t, typename = ::kj::EnableIf< ::kj::canConvert<_t*, Client*>()>>
  Client(::kj::Promise<_t>&& promise);
  Client(::kj::Exception&& exception);
  Client(Client&) = default;
  Client(Client&&) = default;
  Client& operator=(Client& other);
  Client& operator=(Client&& other);

  ::capnp::Request< ::Sample::Subscriber::PushMessageParams,  ::Sample::Subscriber::PushMessageResults> pushMessageRequest(
      ::kj::Maybe< ::capnp::MessageSize> sizeHint = nullptr);

protected:
  Client() = default;
};

class Sample::Subscriber::Server
    : public virtual ::capnp::Capability::Server {
public:
  typedef Subscriber Serves;

  ::capnp::Capability::Server::DispatchCallResult dispatchCall(
      uint64_t interfaceId, uint16_t methodId,
      ::capnp::CallContext< ::capnp::AnyPointer, ::capnp::AnyPointer> context)
      override;

protected:
  typedef  ::Sample::Subscriber::PushMessageParams PushMessageParams;
  typedef  ::Sample::Subscriber::PushMessageResults PushMessageResults;
  typedef ::capnp::CallContext<PushMessageParams, PushMessageResults> PushMessageContext;
  virtual ::kj::Promise<void> pushMessage(PushMessageContext context);

  inline  ::Sample::Subscriber::Client thisCap() {
    return ::capnp::Capability::Server::thisCap()
        .template castAs< ::Sample::Subscriber>();
  }

  ::capnp::Capability::Server::DispatchCallResult dispatchCallInternal(
      uint16_t methodId,
      ::capnp::CallContext< ::capnp::AnyPointer, ::capnp::AnyPointer> context);
};
#endif  // !CAPNP_LITE

class Sample::Subscriber::PushMessageParams::Reader {
public:
  typedef PushMessageParams Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::Subscriber::PushMessageParams::Builder {
public:
  typedef PushMessageParams Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::Subscriber::PushMessageParams::Pipeline {
public:
  typedef PushMessageParams Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Sample::Subscriber::PushMessageResults::Reader {
public:
  typedef PushMessageResults Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool getResult() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::Subscriber::PushMessageResults::Builder {
public:
  typedef PushMessageResults Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool getResult();
  inline void setResult(bool value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::Subscriber::PushMessageResults::Pipeline {
public:
  typedef PushMessageResults Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Sample::InitializeParams::Reader {
public:
  typedef InitializeParams Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::InitializeParams::Builder {
public:
  typedef InitializeParams Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::InitializeParams::Pipeline {
public:
  typedef InitializeParams Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Sample::InitializeResults::Reader {
public:
  typedef InitializeResults Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool getResult() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::InitializeResults::Builder {
public:
  typedef InitializeResults Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool getResult();
  inline void setResult(bool value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::InitializeResults::Pipeline {
public:
  typedef InitializeResults Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Sample::SubscribeParams::Reader {
public:
  typedef SubscribeParams Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool hasSubscriber() const;
#if !CAPNP_LITE
  inline  ::Sample::Subscriber::Client getSubscriber() const;
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::SubscribeParams::Builder {
public:
  typedef SubscribeParams Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool hasSubscriber();
#if !CAPNP_LITE
  inline  ::Sample::Subscriber::Client getSubscriber();
  inline void setSubscriber( ::Sample::Subscriber::Client&& value);
  inline void setSubscriber( ::Sample::Subscriber::Client& value);
  inline void adoptSubscriber(::capnp::Orphan< ::Sample::Subscriber>&& value);
  inline ::capnp::Orphan< ::Sample::Subscriber> disownSubscriber();
#endif  // !CAPNP_LITE

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::SubscribeParams::Pipeline {
public:
  typedef SubscribeParams Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Sample::Subscriber::Client getSubscriber();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Sample::SubscribeResults::Reader {
public:
  typedef SubscribeResults Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool getResult() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Sample::SubscribeResults::Builder {
public:
  typedef SubscribeResults Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool getResult();
  inline void setResult(bool value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Sample::SubscribeResults::Pipeline {
public:
  typedef SubscribeResults Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

#if !CAPNP_LITE
inline Sample::Client::Client(decltype(nullptr))
    : ::capnp::Capability::Client(nullptr) {}
inline Sample::Client::Client(
    ::kj::Own< ::capnp::ClientHook>&& hook)
    : ::capnp::Capability::Client(::kj::mv(hook)) {}
template <typename _t, typename>
inline Sample::Client::Client(::kj::Own<_t>&& server)
    : ::capnp::Capability::Client(::kj::mv(server)) {}
template <typename _t, typename>
inline Sample::Client::Client(::kj::Promise<_t>&& promise)
    : ::capnp::Capability::Client(::kj::mv(promise)) {}
inline Sample::Client::Client(::kj::Exception&& exception)
    : ::capnp::Capability::Client(::kj::mv(exception)) {}
inline  ::Sample::Client& Sample::Client::operator=(Client& other) {
  ::capnp::Capability::Client::operator=(other);
  return *this;
}
inline  ::Sample::Client& Sample::Client::operator=(Client&& other) {
  ::capnp::Capability::Client::operator=(kj::mv(other));
  return *this;
}

#endif  // !CAPNP_LITE
#if !CAPNP_LITE
inline Sample::Subscriber::Client::Client(decltype(nullptr))
    : ::capnp::Capability::Client(nullptr) {}
inline Sample::Subscriber::Client::Client(
    ::kj::Own< ::capnp::ClientHook>&& hook)
    : ::capnp::Capability::Client(::kj::mv(hook)) {}
template <typename _t, typename>
inline Sample::Subscriber::Client::Client(::kj::Own<_t>&& server)
    : ::capnp::Capability::Client(::kj::mv(server)) {}
template <typename _t, typename>
inline Sample::Subscriber::Client::Client(::kj::Promise<_t>&& promise)
    : ::capnp::Capability::Client(::kj::mv(promise)) {}
inline Sample::Subscriber::Client::Client(::kj::Exception&& exception)
    : ::capnp::Capability::Client(::kj::mv(exception)) {}
inline  ::Sample::Subscriber::Client& Sample::Subscriber::Client::operator=(Client& other) {
  ::capnp::Capability::Client::operator=(other);
  return *this;
}
inline  ::Sample::Subscriber::Client& Sample::Subscriber::Client::operator=(Client&& other) {
  ::capnp::Capability::Client::operator=(kj::mv(other));
  return *this;
}

#endif  // !CAPNP_LITE
inline bool Sample::Subscriber::PushMessageResults::Reader::getResult() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline bool Sample::Subscriber::PushMessageResults::Builder::getResult() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Sample::Subscriber::PushMessageResults::Builder::setResult(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Sample::InitializeResults::Reader::getResult() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline bool Sample::InitializeResults::Builder::getResult() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Sample::InitializeResults::Builder::setResult(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Sample::SubscribeParams::Reader::hasSubscriber() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Sample::SubscribeParams::Builder::hasSubscriber() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
#if !CAPNP_LITE
inline  ::Sample::Subscriber::Client Sample::SubscribeParams::Reader::getSubscriber() const {
  return ::capnp::_::PointerHelpers< ::Sample::Subscriber>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Sample::Subscriber::Client Sample::SubscribeParams::Builder::getSubscriber() {
  return ::capnp::_::PointerHelpers< ::Sample::Subscriber>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Sample::Subscriber::Client Sample::SubscribeParams::Pipeline::getSubscriber() {
  return  ::Sample::Subscriber::Client(_typeless.getPointerField(0).asCap());
}
inline void Sample::SubscribeParams::Builder::setSubscriber( ::Sample::Subscriber::Client&& cap) {
  ::capnp::_::PointerHelpers< ::Sample::Subscriber>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(cap));
}
inline void Sample::SubscribeParams::Builder::setSubscriber( ::Sample::Subscriber::Client& cap) {
  ::capnp::_::PointerHelpers< ::Sample::Subscriber>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), cap);
}
inline void Sample::SubscribeParams::Builder::adoptSubscriber(
    ::capnp::Orphan< ::Sample::Subscriber>&& value) {
  ::capnp::_::PointerHelpers< ::Sample::Subscriber>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Sample::Subscriber> Sample::SubscribeParams::Builder::disownSubscriber() {
  return ::capnp::_::PointerHelpers< ::Sample::Subscriber>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#endif  // !CAPNP_LITE

inline bool Sample::SubscribeResults::Reader::getResult() const {
  return _reader.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline bool Sample::SubscribeResults::Builder::getResult() {
  return _builder.getDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Sample::SubscribeResults::Builder::setResult(bool value) {
  _builder.setDataField<bool>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

