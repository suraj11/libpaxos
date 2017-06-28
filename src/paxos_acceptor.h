#pragma once

#include <memory>
#include <thread>

#include "paxos.grpc.pb.h"

namespace libpaxos {

class LibPaxosAcceptor : public Acceptor::Service {
 public:
	LibPaxosAcceptor();
  ~LibPaxosAcceptor();
	grpc::Status getLastVote(grpc::ServerContext*, const NextRound* request, LastVote* response) override;
	grpc::Status beginRound(grpc::ServerContext*, const BeginRound* request, Voted* response) override;
	grpc::Status success(grpc::ServerContext*, const Value* request, Ok* response) override;
 private:
	void mainLoop();
  uint64_t value_ = 0;
  uint64_t nextRound_ = 0;
  uint64_t prevVote_ = 0;
  uint64_t prevValue_ = 0;

  std::thread thread_;
  std::unique_ptr<grpc::Server> server_;
};

} // libpaxos
