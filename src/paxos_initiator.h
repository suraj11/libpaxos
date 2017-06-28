
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

class LibPaxosInitiator {
private:
  uint64_t value;
  uint64_t lastTried = 0;

public:
  void setVal(uint64_t val);
  uint64_t getVal(void);
  void setLastTried(void);
  uint64_t getLastTried(void);
  uint64_t getNextRoundNumber(void);
  int initiateRound(void);
};

