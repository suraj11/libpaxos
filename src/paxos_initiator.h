#pragma once

#include "paxos.grpc.pb.h"

namespace libpaxos {

class LibPaxosInitiator {
 private:
  std::vector<std::string> address_;
  uint64_t value_ = 0;
  uint64_t lastTried_ = 0;
 public:
  LibPaxosInitiator(void);
  int initiateRound(void);
};

}
