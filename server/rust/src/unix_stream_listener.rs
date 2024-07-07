//use crate::sample_capnp::sample;
use std::io;
use std::pin::Pin;
use std::task::{Context, Poll};

pub struct UnixStreamListener {
    inner: tokio::net::UnixListener,
}

impl UnixStreamListener  {
    pub async fn new(path: &str) -> Result<UnixStreamListener, Box<dyn std::error::Error>> {
        let stream = tokio::net::UnixListener::bind(path)?;
        Ok(UnixStreamListener { inner: stream } )
    }

    pub async fn accept(self: &Self) -> io::Result<tokio::net::UnixStream> {
        match self.inner.accept().await {
            io::Result::Ok((stream, _)) => { return io::Result::Ok(stream); },
            io::Result::Err(err) => { return io::Result::Err(err); },
        }
    }
}
