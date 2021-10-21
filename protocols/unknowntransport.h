#ifndef UNKNOWNTRANSPORT_H
#define UNKNOWNTRANSPORT_H

#include <QObject>
#include <protocols/basetransport.hpp>
#include <string>
#include <vector>

using namespace std;

class UnknownTransport : public BaseTransport {
  Q_OBJECT
 public:
  UnknownTransport();

  virtual void deserializeHeader(const u_char *bytes, int offset);
  virtual bool isHeaderInvalid();
  virtual QString getFullData();
};

#endif  // UNKNOWNTRANSPORT_H