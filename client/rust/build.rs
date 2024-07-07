use std::fs;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let origin_cap_file_path = "../../interface/sample.cap";
    let temp_cap_file_path = "src/sample.cap";
    fs::copy(origin_cap_file_path, temp_cap_file_path)?;
    let ret = capnpc::CompilerCommand::new()
        .file(temp_cap_file_path)
        .output_path(".")
        .run()?;
    fs::remove_file(temp_cap_file_path)?;
    Ok(ret)
}