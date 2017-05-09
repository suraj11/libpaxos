#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <gflags/gflags.h>

#include "paxos.grpc.pb.h"

DEFINE_uint32(port, 50051, "Listen port");

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using namespace libpaxos;

class AcceptorImpl : public Acceptor::Service {
  Status getLastVote(ServerContext*, const NextRound* request, LastVote* response) override {
		return Status::OK;
  }
  Status beginRound(ServerContext*, const BeginRound* request, Voted* response) override {
		return Status::OK;
  }
  Status success(ServerContext*, const Value* request) {
		return Status::OK;
  }
};

int main(int argc, char** argv) {
	gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::string server_address = "0.0.0.0:" + std::to_string(FLAGS_port);
  ServerBuilder builder;
  AcceptorImpl service;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
