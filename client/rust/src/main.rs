pub mod sample_capnp {
    include!("sample_capnp.rs");
}

pub mod client;
pub mod unix_stream_proxy;
use std::sync::{Arc, Mutex};
use tokio::signal::unix::{signal, SignalKind};

#[tokio::main(flavor = "current_thread")]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let signal_received = Arc::new(Mutex::new(false));
    let signal_received_cloned = signal_received.clone();
    tokio::spawn(async move {
        loop {
            let mut alarm = signal(SignalKind::alarm()).unwrap();
            let mut child = signal(SignalKind::child()).unwrap();
            let mut hangup= signal(SignalKind::hangup()).unwrap();
            let mut interrupt= signal(SignalKind::interrupt()).unwrap();
            let mut io= signal(SignalKind::io()).unwrap();
            let pipe= signal(SignalKind::pipe()).unwrap();
            let mut quite= signal(SignalKind::quit()).unwrap();
            let mut terminate= signal(SignalKind::terminate()).unwrap();
            tokio::select! {
                _ = alarm.recv() => println!("SIGALARM"),
                _ = child.recv() => println!("SIGCHILD"),
                _ = hangup.recv() => println!("SIGHANGUP"),
                _ = interrupt.recv() => println!("SIGINTERRUPT"),
                _ = io.recv() => println!("SIGIO"),
            }
            break;
        }
        let mut a = signal_received_cloned.lock().unwrap();
        *a = true;
    });

    //client::try_main(signal_received).await;
    client::main(signal_received).await;
    Ok(())
}
