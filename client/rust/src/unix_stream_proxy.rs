//use crate::sample_capnp::sample;
use std::io;
use std::pin::Pin;
use std::task::{Context, Poll};

pub struct UnixStreamProxy {
    inner: tokio::net::UnixStream,
}

impl UnixStreamProxy  {
    pub async fn new(path: &str) -> Result<UnixStreamProxy, Box<dyn std::error::Error>> {
        let stream = tokio::net::UnixStream::connect(path).await?;
        Ok(UnixStreamProxy { inner: stream } )
    }
}

impl tokio::io::AsyncRead for UnixStreamProxy {
    fn poll_read(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        buf: &mut tokio::io::ReadBuf<'_>,
    ) -> Poll<io::Result<()>> {
        let inner = unsafe { 
            self.map_unchecked_mut(|s| &mut s.inner)
        };
        inner.poll_read(cx, buf)
    }
}

impl tokio::io::AsyncWrite for UnixStreamProxy {
    fn poll_write(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        buf: &[u8],
    ) -> Poll<Result<usize, io::Error>> {
        let inner = unsafe { 
            self.map_unchecked_mut(|s| &mut s.inner)
        };
        inner.poll_write(cx, buf)
    }

    fn poll_flush(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let inner = unsafe { 
            self.map_unchecked_mut(|s| &mut s.inner)
        };
        inner.poll_flush(cx)
    }

    fn poll_shutdown(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let inner = unsafe { 
            self.map_unchecked_mut(|s| &mut s.inner)
        };
        inner.poll_shutdown(cx)
    }
}
