#include "paxos_acceptor.h"

#include <unistd.h>
#include <gflags/gflags.h>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "paxos.grpc.pb.h"

DEFINE_uint32(libpaxos_port, 50051, "Listen port");

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

namespace libpaxos {

LibPaxosAcceptor::LibPaxosAcceptor() {
  std::string server_address = "127.0.0.1:" + std::to_string(FLAGS_libpaxos_port);
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(this);
  server_ = builder.BuildAndStart();

  thread_ = std::thread([this]() {
		mainLoop();
	});
	sleep(3);
}

LibPaxosAcceptor::~LibPaxosAcceptor() {
  server_->Shutdown();
  thread_.join();
}

Status LibPaxosAcceptor::getLastVote(ServerContext*, const NextRound* request, LastVote* response) {
  const auto round = request->roundnumber();
  response->set_roundnumber(round);
	std::cout << "in last vote" << std::endl;
  if (round > nextRound_) {
    nextRound_ = round;
    response->set_lastvalue(prevValue_);
    response->set_lastround(prevVote_);
	  response->set_accepted(true);
  } else {
    response->set_lastround(nextRound_);
	  response->set_accepted(false);
  }
  return Status::OK;
}

Status LibPaxosAcceptor::beginRound(ServerContext*, const BeginRound* request, Voted* response) {
  const auto round = request->roundnumber();
  response->set_roundnumber(round);
  if (round == nextRound_) {
		prevVote_ = round;
    prevValue_ = request->value();
    response->set_lastround(0);
	  response->set_accepted(true);
  } else {
    response->set_lastround(nextRound_);
	  response->set_accepted(false);
  }
  return Status::OK;
}

Status LibPaxosAcceptor::success(ServerContext*, const Value* request, Ok* response) {
 response->set_roundnumber(request->roundnumber());
 return Status::OK;
}

void LibPaxosAcceptor::mainLoop() {
	std::cout << "in main loop" << std::endl;
  server_->Wait();
}

} // libpaxos
