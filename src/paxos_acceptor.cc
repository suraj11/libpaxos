#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <gflags/gflags.h>

#include "paxos.grpc.pb.h"

DEFINE_uint32(libpaxos_port, 50051, "Listen port");

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using namespace libpaxos;

class AcceptorImpl : public Acceptor::Service {
 public:
  Status getLastVote(ServerContext*, const NextRound* request, LastVote* response) override {
    const auto round = request->roundnumber();
    response->set_roundnumber(round);
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
  Status beginRound(ServerContext*, const BeginRound* request, Voted* response) override {
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
  Status success(ServerContext*, const Value* request, Ok* response) {
   response->set_roundnumber(request->roundnumber());
   return Status::OK;
  }
 private:
  uint64_t value_ = 0;
  uint64_t nextRound_ = 0;
  uint64_t prevVote_ = 0;
	uint64_t prevValue_ = 0;
};
