# TCP Connect and Process

A simple application that can connect to a server using TCP protocol, reads a multiline message from the server with 
whitelines until a hex string. It then processes the hex string by decoding using hex and decompressing using gzip. It finally, rewrites the the decoded string
to the server and reads the final response of the server.

## Dependencies
* C++ Boost - *Version specified in ```conanfile.txt```*

## Setup
This project's packages are managed using conan. 

```bash
pip install --user conan
```

The project also uses cmake and ninja generators.
```bash
sudo apt install build-essential cmake ninja-build 
```

## Usage

There an assistive build script to build the project.

```bash
    chmod +x build.sh  && ./build.sh 
```