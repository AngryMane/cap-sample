use crate::sample_capnp::sample;

use capnp_rpc::{rpc_twoparty_capnp, twoparty, RpcSystem};
use futures::AsyncReadExt;
use tokio_util::compat::TokioAsyncReadCompatExt;
use std::{thread, time, sync::Arc, sync::Mutex};
use crate::unix_stream_proxy;

pub async fn main(signal: Arc<Mutex<bool>>) -> Result<(), Box<dyn std::error::Error>> {
    tokio::task::LocalSet::new().run_until(try_main(signal)).await
}

pub struct SampleClient {
    client: sample::Client,
    event_loop_handler: tokio::task::JoinHandle<Result<(), capnp::Error>>,
}

impl SampleClient {
    pub async fn new(socket_path: &str) -> Result<SampleClient, Box<dyn std::error::Error>>{
        let unix_stream_proxy = unix_stream_proxy::UnixStreamProxy::new(socket_path).await?;
        let (unix_stream_reader, unix_stream_writer) = unix_stream_proxy.compat().split();
        let network = Box::new(twoparty::VatNetwork::new(
            unix_stream_reader,
            unix_stream_writer,
            rpc_twoparty_capnp::Side::Client,
            Default::default(),
        ));

        let mut rpc_system = RpcSystem::new(network, None);
        let client: sample::Client = rpc_system.bootstrap(rpc_twoparty_capnp::Side::Server);
        //let event_loop_handler = tokio::task::spawn_local(rpc_system);
        let event_loop_handler = tokio::task::spawn_local(rpc_system);

        return Ok(SampleClient { client, event_loop_handler });
    }

    pub async fn initialize(self: &Self) -> Result<bool, Box<dyn std::error::Error>> {
        let initialize_request = self.client.initialize_request();
        let value = initialize_request.send().promise.await?;
        let result = value.get()?.get_result();
        Ok(result)
    }
}

pub async fn try_main(signal: Arc<Mutex<bool>>) -> Result<(), Box<dyn std::error::Error>> {
    let socket_path = "./sample.sock";
    let client = SampleClient::new(socket_path).await?;

    loop {
        let initialize_ret = client.initialize().await?;
        println!("{}", initialize_ret);
        let ten_millis = time::Duration::from_millis(2000);
        thread::sleep(ten_millis);
        let a = signal.lock().unwrap();
        if *a == true {
            break;
        }
    }

    client.event_loop_handler.await?;

    Ok(())
}