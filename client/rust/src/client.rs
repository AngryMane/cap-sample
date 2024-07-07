use crate::sample_capnp::sample;
use capnp_rpc::{rpc_twoparty_capnp, twoparty, RpcSystem};
use futures::AsyncReadExt;
use tokio_util::compat::TokioAsyncReadCompatExt;
use std::{thread, time};

use crate::unix_stream_proxy;


#[derive(Clone, Copy)]
pub struct PowerFunction;

pub async fn main() -> Result<(), Box<dyn std::error::Error>> {
    tokio::task::LocalSet::new().run_until(try_main()).await
}

async fn try_main() -> Result<(), Box<dyn std::error::Error>> {
    let socket_path = "./sample.sock";
    let unix_stream_proxy = unix_stream_proxy::UnixStreamProxy::new(socket_path).await?;
    let (unix_stream_reader, unix_stream_writer) = unix_stream_proxy.compat().split();
    let network = Box::new(twoparty::VatNetwork::new(
        unix_stream_reader,
        unix_stream_writer,
        rpc_twoparty_capnp::Side::Client,
        Default::default(),
    ));

    let mut rpc_system = RpcSystem::new(network, None);
    let sample: sample::Client = rpc_system.bootstrap(rpc_twoparty_capnp::Side::Server);
    tokio::task::spawn_local(rpc_system);

    loop {
        let initialize_request = sample.initialize_request();
        let value = initialize_request.send().promise.await?;
        let result = value.get()?.get_result();
        println!("{}", result);
        let ten_millis = time::Duration::from_millis(2000);
        thread::sleep(ten_millis);
    }


    Ok(())
}