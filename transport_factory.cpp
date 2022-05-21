#include "transport_factory.h"

#include "protocols/icmp.h"
#include "protocols/tcp.h"
#include "protocols/udp.h"
#include "protocols/unknown_transport.h"

std::unique_ptr<BaseTransport> TransportFactory::makeTransport(int protocol) {
  switch (protocol) {
    case 1:
      return std::make_unique<Icmp>();
    case 6:
      return std::make_unique<Tcp>();
    case 17:
      return std::make_unique<Udp>();
    default:
      return std::make_unique<UnknownTransport>();
  }
}
