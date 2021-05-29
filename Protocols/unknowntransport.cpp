#include "unknowntransport.h"

UnknownTransport::UnknownTransport()
{

}

void UnknownTransport::deserializeHeader(const u_char *bytes, int offset) {
    //
}

bool UnknownTransport::isHeaderInvalid() {
    //
    return false;
}

QString UnknownTransport::getFullData() {
    return "\nProtocol unknown, no data available\n";
}
