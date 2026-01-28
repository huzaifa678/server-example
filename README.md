# Server example using C++

## Basic Implementation Of gRPC And REST Server Using C++ Applying It's OOP Concepts To Implement A Simple Multi-Threaded Server Setup

### REST Server:

    Acts as the gateway server calling the stub for the gRPC server to serve the request

### gRPC Server:

    Responds to the stub called by the REST server to serve the client

### Basic Flow:

    Implemented a sample C++ client to send the request to the REST server which forwards it to the gRPC server by calling the stub

    gRPC server calls the gRPC service in response to the stub which the executes the rpc method implementation.

    runREST Thread: Executes the function which calls the default main Server class implementation of the virtual function

    handleClient Thread: Executes the logic for the REST server to create the gRPC channel, call the stub and wait for the response

    runGRPC Thread: After runREST thread is detached this thread executes the runGRPC method calling the implemented start() virtual function to

    start the gRPC server and register the service

### OOP Design:

* **Server class**: Parent class which defines the virtual function start() and pure virtual function handleClient() for the gRPC and REST server
* **gRPC Server class**: Implement's the virtual function to start the server and registers the gRPC service class
* **REST Server class**: Implement's the virtual function to handle the client request involving creating the gRPC channel and calling the stub
* **gRPC Service class**: Implement's the generated protoc functions to execute the response logic

### Tech Stack:

* **C++:** Used for implementing the Servers
* **gRPC**: Used for RPC client stubs and as a server
* **Protoc**: Compiler for generating .cc and .h files for the gRPC server to implement and for the REST server to call the stub
* **CMake:** Used for compiling and building the single executable using the header and cpp files of the servers

### Guidelines to start

1. Make the build directory and cd into it

    ```bash
    	mkdir build

    ```bash
   	 cd build

2. Generate the CMake confiugrations

    ```bash
    	cmake ..

3. Build the files

    ```bash
    	make

4. Run the executable

    ```bash
    	./server-example
