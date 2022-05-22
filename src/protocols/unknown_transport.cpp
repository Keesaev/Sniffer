#include "unknown_transport.h"

void UnknownTransport::deserializeHeader(const u_char* bytes, int offset) {
  Q_UNUSED(bytes)
  Q_UNUSED(offset)
  //
}

bool UnknownTransport::isHeaderInvalid() const {
  //
  return false;
}

QString UnknownTransport::getFullData() const {
  return "\nProtocol unknown, no data available\n";
}
