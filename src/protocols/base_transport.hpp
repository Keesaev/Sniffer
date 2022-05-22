#ifndef BASETRANSPORT_H
#define BASETRANSPORT_H

#include <QString>

class BaseTransport {
 public:
  virtual void deserializeHeader(const u_char* bytes, int offset) = 0;

  virtual bool isHeaderInvalid() const = 0;

  virtual QString getFullData() const = 0;

  // TODO dtor
  virtual ~BaseTransport() = default;
};

#endif  // BASETRANSPORT_H
