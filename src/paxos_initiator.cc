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
#include <glog/logging.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using libpaxos::NextRound;
using libpaxos::LastVote;
using libpaxos::BeginRound;
using libpaxos::Voted;
using libpaxos::Ok;
using libpaxos::Value;
using libpaxos::Acceptor;
using namespace std;

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

int func(int argc, char** argv) {

  InitiatorClient client;
  google::InitGoogleLogging(argv[0]);

  std::ifstream file("../src/acceptor.conf");
  std::string str;
  vector<string> address;
  while (std::getline(file, str))
  {
    address.push_back(str);
  }

  vector<std::shared_ptr<Channel>> channel(address.size());
  vector<LastVote> response(address.size());
  uint64_t maxRound = 0;
  uint64_t maxVal = 1;
  uint64_t thisRoundNum = client.getNextRoundNumber();
  client.setLastTried();

/* Next ballot */
  for(int i=0; i < address.size(); i++) {
      channel[i] = grpc::CreateChannel(address[i], grpc::InsecureChannelCredentials());
      std::unique_ptr<Acceptor::Stub> stub_(Acceptor::NewStub(channel[i]));
      ClientContext contextGetlastVote;
      NextRound round;
      cout << "created channel for "<<address[i]<< "\n";
      cout<<"before getting last vote.\n";
      round.set_roundnumber(thisRoundNum);
      Status status = stub_->getLastVote(&contextGetlastVote, round, &response[i]);
      cout<<"got last vote.\n";

      if(response[i].accepted() && response[i].lastround() > maxRound) {
        maxRound = response[i].lastround();
        maxVal = response[i].lastvalue();
      }
  }


/* BeginBallot */
  for(int i=0; i < address.size(); i++) {
    channel[i] = grpc::CreateChannel(address[i], grpc::InsecureChannelCredentials());
    std::unique_ptr<Acceptor::Stub> stub_(Acceptor::NewStub(channel[i]));

    ClientContext contextBeginRound;
    BeginRound br;
    br.set_roundnumber(thisRoundNum);
    br.set_value(maxVal);
    Voted vote;
    cout<<"before begin round\n";
    stub_->beginRound(&contextBeginRound, br, &vote);

    if(vote.accepted() && vote.roundnumber() == thisRoundNum) {
      ClientContext contextSuccess;
      Value v;
      Ok k;
      cout<<"before success.\n";
      client.setVal(maxVal);
      stub_->success(&contextSuccess, v, &k);
    }
   }

  return 0;
}

