#ifndef UNKNOWNTRANSPORT_H
#define UNKNOWNTRANSPORT_H

#include "base_transport.hpp"

// TODO: remove and add implementations to base class

class UnknownTransport : public BaseTransport {
 public:
  virtual void deserializeHeader(const u_char* bytes, int offset) final;
  virtual bool isHeaderInvalid() const final;
  virtual QString getFullData() const final;
};

#endif  // UNKNOWNTRANSPORT_H
