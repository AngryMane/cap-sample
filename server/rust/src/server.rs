use std::{cell::RefCell, collections::HashMap, rc::Rc};

use crate::sample_capnp::sample;
use crate::sample_capnp::sample::subscriber;
use capnp_rpc::{pry, rpc_twoparty_capnp, twoparty, RpcSystem};
use futures::{AsyncReadExt, TryFutureExt};
use tokio_util::compat::TokioAsyncReadCompatExt;

use crate::unix_stream_listener;

type SubscriberMap = HashMap<u64, subscriber::Client>;

struct SampleServerImpl{
    next_id: u64,
    subscribers: Rc<RefCell<SubscriberMap>>,
}

impl SampleServerImpl {
    pub fn new() -> (Self, Rc<RefCell<SubscriberMap>>) {
        let subscribers = Rc::new(RefCell::new(SubscriberMap::new()));
        (
            Self {
                next_id: 0,
                subscribers: subscribers.clone(),
            },
            subscribers,
        )
    }
}

impl sample::Server for  SampleServerImpl {
    fn initialize(&mut self, _: sample::InitializeParams<>, mut result: sample::InitializeResults<>) -> ::capnp::capability::Promise<(), ::capnp::Error> { 
        println!("initialize called");
        result.get().set_result(true);
        ::capnp::capability::Promise::ok(())
    }

    fn subscribe(&mut self, param: sample::SubscribeParams<>, mut result: sample::SubscribeResults<>) -> ::capnp::capability::Promise<(), ::capnp::Error> { 
        println!("subscribe called");
        self.subscribers.borrow_mut().insert(
            self.next_id, 
            pry!(pry!(param.get()).get_subscriber()),
        );
        result.get().set_result(true);
        self.next_id += 1;
        ::capnp::capability::Promise::ok(())
    }
}

pub async fn start() -> Result<(), Box<dyn std::error::Error>> {
    let socket_path = "./sample.sock";

    tokio::task::LocalSet::new()
        .run_until(async move {
            let (sample, subscribers) = SampleServerImpl::new();
            let sample: sample::Client = capnp_rpc::new_client(sample);
            let unix_stream_proxy = unix_stream_listener::UnixStreamListener::new(socket_path).await?;
            let listener_thread = async move {
                loop{
                    let stream = unix_stream_proxy.accept().await.unwrap();
                    let (unix_stream_reader, unix_stream_writer) = stream.compat().split();
                    let network = twoparty::VatNetwork::new(
                        unix_stream_reader,
                        unix_stream_writer,
                        rpc_twoparty_capnp::Side::Server,
                        Default::default(),
                    );
                    let rpc_system = RpcSystem::new(Box::new(network), Some(sample.clone().client));
                    tokio::task::spawn_local(rpc_system.map_err(|e| println!("error: {e:?}")));
                }
            };
            listener_thread.await;
 
            Ok(())
        })
        .await
}