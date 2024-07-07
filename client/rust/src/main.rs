pub mod sample_capnp {
    include!("sample_capnp.rs");
}

pub mod client;
pub mod unix_stream_proxy;

#[tokio::main(flavor = "current_thread")]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    return client::main().await;
}
