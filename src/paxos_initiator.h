#pragma once

#include "paxos.grpc.pb.h"

namespace libpaxos {

class LibPaxosInitiator {
 private:
  uint64_t value_ = 0;
  uint64_t lastTried_ = 0;
 public:
  void setVal(uint64_t val);
  uint64_t getVal(void);
  void setLastTried(void);
  uint64_t getLastTried(void);
  uint64_t getNextRoundNumber(void);
  int initiateRound(void);
};

}
