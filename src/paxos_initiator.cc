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
using libpaxos::NextRound;
using libpaxos::LastVote;
using libpaxos::BeginRound;
using libpaxos::Voted;
using libpaxos::Ok;
using libpaxos::Value;
using libpaxos::Acceptor;
using namespace std;

class InitiatorClient {
public:
};

int main(int argc, char** argv) {

  InitiatorClient client;

  std::ifstream file("acceptor.conf");
  std::string str;
  vector<string> address;
  while (std::getline(file, str))
  {
    address.push_back(str);
  }

  vector<std::shared_ptr<Channel>> channel(address.size());
  vector<LastVote> response;
  int maxRound = INT_MIN;
  int maxVal = INT_MIN;
  uint64_t lastTried = 1;

/* Next ballot */
  for(int i=0; i < address.size(); i++) {
      channel[i] = grpc::CreateChannel(address[i], grpc::InsecureChannelCredentials());
      std::unique_ptr<Acceptor::Stub> stub_(Acceptor::NewStub(channel[i]));
      ClientContext contextGetlastVote;
      NextRound round;
      cout<< "created channel for "<<address[i]<< "\n";
      round.set_roundnumber(lastTried);
      cout<<"before getting last vote.\n";
      Status status = stub_->getLastVote(&contextGetlastVote, round, &response[i]);
      cout<<"got last vote.\n";

/*      if(response[i].lastround() > maxRound) {
        maxRound = response[i].lastround();
        maxVal = response[i].lastvalue();
        maxVal = 1;
      }
*/
  }


/* BeginBallot */
  for(int i=0; i < address.size(); i++) {
    channel[i] = grpc::CreateChannel(address[i], grpc::InsecureChannelCredentials());
    std::unique_ptr<Acceptor::Stub> stub_(Acceptor::NewStub(channel[i]));

    ClientContext contextBeginRound;
    BeginRound br;
    br.set_roundnumber(lastTried);
    br.set_value(maxVal);
    Voted vote;
 cout<<"before begin round\n";
    stub_->beginRound(&contextBeginRound, br, &vote);

//    if(vote.lastround() == lastTried) {
      ClientContext contextSuccess;
      Value v;
      Ok k;
      cout<<"before success.\n";
      stub_->success(&contextSuccess, v, &k);
//    }
   }

  return 0;
}

