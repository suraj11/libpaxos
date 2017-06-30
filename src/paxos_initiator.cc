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

namespace libpaxos {

LibPaxosInitiator::LibPaxosInitiator() {
  std::ifstream file("../src/acceptor.conf");
  std::string str;
  while (std::getline(file, str)) {
    address_.push_back(str);
  }
}

int LibPaxosInitiator::initiateRound() {
  std::vector<std::shared_ptr<Channel>> channel(address_.size());
  std::vector<LastVote> response(address_.size());
  uint64_t maxRound = 0;
  uint64_t maxVal = 1;
  uint64_t thisRoundNum = lastTried_++;

  for (int i=0; i < address_.size(); i++) {
    channel[i] = grpc::CreateChannel(address_[i], grpc::InsecureChannelCredentials());
  }

  /* Next ballot */
  for(int i=0; i < address_.size(); i++) {
    auto stub_ = Acceptor::NewStub(channel[i]);
    ClientContext contextGetlastVote;
    NextRound round;
    CompletionQueue cq;
    std::cout << "created channel for " << address_[i] << std::endl;
    std::cout << "before getting last vote." << std::endl;
    round.set_roundnumber(thisRoundNum);
    auto rpc = stub_->AsyncgetLastVote(&contextGetlastVote, round, &cq);
    std::cout << "got last vote." << std::endl;

    Status status;
    rpc->Finish(&response[i], &status, (void*)&i);

    void* got_tag;
    bool ok = false;
    std::cout << "before cq" << std::endl;
    cq.Next(&got_tag, &ok);
    if (ok && got_tag == (void*)&i) {
      std::cout << response[i].lastvalue() << std::endl;
      if(response[i].accepted() && response[i].lastround() > maxRound) {
        maxRound = response[i].lastround();
        maxVal = response[i].lastvalue();
      }
    } else {
      std::cout << "INVAID!!!" << std::endl;
    }
  }

  /* BeginBallot */
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
