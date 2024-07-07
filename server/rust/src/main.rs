pub mod sample_capnp {
    include!("sample_capnp.rs");
}

pub mod server;
pub mod unix_stream_listener;

#[tokio::main(flavor = "current_thread")]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    return server::start().await;
}
