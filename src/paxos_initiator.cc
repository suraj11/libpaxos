#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

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


int main(int argc, char** argv) {
  std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  std::unique_ptr<Acceptor::Stub> stub_(Acceptor::NewStub(channel));
  uint64_t lastTried = 1;
  ClientContext context;

  NextRound round;
  LastVote response;
//  round.set_roundNumber(lastTried);
  stub_->getLastVote(&context, round, &response);
/*
//  cur_val = lastVote.get_lastValue();

  BeginRound br;
//  br.set_roundNumber(lastTried);
//  br.set_value(cur_val);
  Voted vote;
  stub_->beginRound(&context, br, &vote);

//  if(Voted.get_lastRound == lastTried) {
    Value v;
    Ok k;
    stub_->success(&context, v, &k);
//  }  
*/
  return 0;
}

