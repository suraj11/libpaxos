#include "paxos_initiator.h"

#include <fstream>

#include <gflags/gflags.h>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/create_channel.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::ClientAsyncResponseReaderInterface;

namespace libpaxos {

LibPaxosInitiator::LibPaxosInitiator() {
  std::ifstream file;
  std::cout<<"initializing\n";
  file.open("/home/ubuntu/suraj/libpaxos/src/acceptor.conf");
  std::string str;
  while (std::getline(file, str)) {
    std::cout<<"address: "<< str<<"\n";
    address_.push_back(str);
  }
}

int LibPaxosInitiator::initiateRound() {
  std::vector<std::shared_ptr<Channel>> channel(address_.size());
  uint64_t maxRound = 0;
  uint64_t maxVal = 1;
  uint64_t thisRoundNum = lastTried_++;

  for (int i=0; i < address_.size(); i++) {
    channel[i] = grpc::CreateChannel(address_[i], grpc::InsecureChannelCredentials());
  }

  /* Next ballot */
  CompletionQueue cq;
	using Rpc = std::unique_ptr<ClientAsyncResponseReaderInterface<LastVote>>;
	std::vector<std::unique_ptr<Acceptor::Stub>> stubs;
	std::vector<Rpc> rpcs;
  std::vector<ClientContext> contextGetlastVote(address_.size());
	std::vector<Status> status(address_.size());
	std::vector<NextRound> round(address_.size());
  std::vector<LastVote> response(address_.size());

  for(int i=0; i < address_.size(); i++) {
    stubs.push_back(Acceptor::NewStub(channel[i]));
    round[i].set_roundnumber(thisRoundNum);
    rpcs.emplace_back(stubs[i]->AsyncgetLastVote(&contextGetlastVote[i], round[i], &cq));
    rpcs.back()->Finish(&response[i], &status[i], reinterpret_cast<void*>(i));
  }

	for (int j = 0; j < std::max((size_t) 1, address_.size() / 2 + 1); j++) {
    void* got_tag;
    bool ok = false;
    std::cout << "before cq" << std::endl;
    cq.Next(&got_tag, &ok);
		std::cout << "after cq" << std::endl;
    if (ok) {
			const auto i = reinterpret_cast<int>(got_tag);
      std::cout << response[i].lastvalue() << std::endl;
      if(response[i].accepted() && response[i].lastround() > maxRound) {
        maxRound = response[i].lastround();
        maxVal = response[i].lastvalue();
      }
    } else {
      std::cout << "INVAID!!!" << std::endl;
    }
  }

  /* Begin ballot */
  for(int i=0; i < address_.size(); i++) {
    auto stub_ = Acceptor::NewStub(channel[i]);

    ClientContext contextBeginRound;
    BeginRound br;
    br.set_roundnumber(thisRoundNum);
    br.set_value(maxVal);
    Voted vote;
    std::cout << "before begin round" << std::endl;
    stub_->beginRound(&contextBeginRound, br, &vote);

    if(vote.accepted() && vote.roundnumber() == thisRoundNum) {
      ClientContext contextSuccess;
      Value v;
      Ok k;
      std::cout << "before success" << std::endl;
      value_ = maxVal;
      stub_->success(&contextSuccess, v, &k);
    }
  }
}

}
