#include "../src/paxos_initiator.h"
#include "../src/paxos_acceptor.h"


int main() {
  libpaxos::LibPaxosInitiator p;
  libpaxos::LibPaxosAcceptor q;

  p.initiateRound();
  return 0;
}
