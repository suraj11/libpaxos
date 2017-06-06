#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <fstream>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "paxos.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using grpc::CompletionQueue;

using libpaxos::NextRound;
using libpaxos::LastVote;
using libpaxos::BeginRound;
using libpaxos::Voted;
using libpaxos::Ok;
using libpaxos::Value;
using libpaxos::Acceptor;

class InitiatorClient {
private:
  uint64_t value;
  uint64_t lastTried;

public:
  InitiatorClient() {
    lastTried = 0;
  }

  void setVal(uint64_t val) {
    value = val;
  }

  uint64_t getVal() {
    return value;
  }

  void setLastTried() {
     lastTried++;
  }

  uint64_t getLastTried() {
    return lastTried;
  }

  uint64_t getNextRoundNumber() {
    return lastTried + 1;
  }
};

int main(int argc, char** argv) {

  InitiatorClient client;

  std::ifstream file("../src/acceptor.conf");
  std::string str;
  std::vector<std::string> address;
  while (std::getline(file, str)) {
    address.push_back(str);
  }

  std::vector<std::shared_ptr<Channel>> channel(address.size());
  std::vector<LastVote> response(address.size());
  uint64_t maxRound = 0;
  uint64_t maxVal = 1;
  uint64_t thisRoundNum = client.getNextRoundNumber();
  client.setLastTried();

  for (int i=0; i < address.size(); i++) {
    channel[i] = grpc::CreateChannel(address[i], grpc::InsecureChannelCredentials());
  }

/* Next ballot */
  for(int i=0; i < address.size(); i++) {
    auto stub_ = Acceptor::NewStub(channel[i]);
    ClientContext contextGetlastVote;
    NextRound round;
    CompletionQueue cq;
    std::cout << "created channel for " << address[i] << std::endl;
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
  for(int i=0; i < address.size(); i++) {
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
      client.setVal(maxVal);
      stub_->success(&contextSuccess, v, &k);
    }
   }

  return 0;
}

