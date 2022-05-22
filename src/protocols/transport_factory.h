#ifndef TRANSPORTFACTORY_H
#define TRANSPORTFACTORY_H

#include "base_transport.hpp"

#include <memory>

class TransportFactory {
 public:
  TransportFactory() = delete;
  static std::unique_ptr<BaseTransport> makeTransport(int protocol);
};

#endif  // TRANSPORTFACTORY_H
