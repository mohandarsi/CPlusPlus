#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "echoInterface.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using RequestReply::Request;
using RequestReply::Response;
using RequestReply::EchoService;


class EchoClient {
public:
    EchoClient(std::shared_ptr<Channel> channel)
            : stub_(EchoService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string SayHello(const std::string &user) {
        // Data we are sending to the server.
        Request request;
        request.set_username(user);

        // Container for the data we expect from the server.
        Response reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->Echo(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<EchoService::Stub> stub_;
};

int main(int argc, char **argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    EchoClient greeter(grpc::CreateChannel(
            "localhost:8888", grpc::InsecureChannelCredentials()));
    std::string user("tovenaar");
    std::string reply = greeter.SayHello(user);
    std::cout << "Received: " << reply << std::endl;

    return 0;
}
