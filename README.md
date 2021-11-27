# TCP Connect and Process

A simple application that can connect to a server using TCP protocol, reads a multiline message from the server with 
whitelines until a hex string. It then processes the hex string by decoding using hex and decompressing using gzip. It finally, rewrites the the decoded string
to the server and reads the final response of the server.

## Dependencies
* C++ Boost version 1.65+ with zlib support
  * if not, download and build zlib source code and link it in cmake
## Setup
* Clone
```bash
git clone <git url>
```
* change directory
```bash
cd <project_dir> && mkdir build
```
* build
```bash
cmake .. && make
```
* execute
```bash
./exec --help  # prints usage
```
