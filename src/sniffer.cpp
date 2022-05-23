// https://www.tcpdump.org/manpages/pcap.3pcap.html
// https://habr.com/ru/post/337840/

#include "sniffer.h"

#include "protocols/base_transport.hpp"
#include "protocols/data_link.h"
#include "protocols/network.h"
#include "protocols/transport_factory.h"
#include "protocols/unknown_transport.h"

#include <QDateTime>
#include <QDebug>

Sniffer::Sniffer(QString const& device)
    : QObject(nullptr),
      m_handle{std::unique_ptr<pcap_t, void (*)(pcap_t*)>(
          pcap_create(device.toLocal8Bit().data(), errbuf),
          [](pcap_t* handle) { pcap_close(handle); })} {
  if (m_handle.get() == nullptr) {
    qDebug() << errbuf;
  } else {
    pcap_set_snaplen(m_handle.get(), 65535);
    pcap_set_promisc(m_handle.get(), 1);
    pcap_set_rfmon(m_handle.get(), 0);
    pcap_set_timeout(m_handle.get(), 1000);
    pcap_set_immediate_mode(m_handle.get(), 1);
    pcap_set_buffer_size(m_handle.get(), PCAP_BUF_SIZE);
    pcap_set_tstamp_type(m_handle.get(), PCAP_TSTAMP_HOST);
    int retVal = pcap_activate(m_handle.get());

    qDebug() << "pcap_activate " << retVal;
  }
}

bool Sniffer::isValid() const {
  return m_handle.get() != nullptr;
}

// Вызываем captureSinglePacket в цикле, контроллируем его
// переменной m_running
void Sniffer::startCapture() {
  m_running = true;
  while (m_running) {
    captureSinglePacket();
  }

  qDebug() << "Finished";
  emit finished();
}

// Захватываем один пакет и издаем сигнал
void Sniffer::captureSinglePacket() {
  pcap_pkthdr* header;
  const u_char* bytes;
  int retVal = pcap_next_ex(m_handle.get(), &header, &bytes);
  if (retVal != 1) {
    return;  // PCAP не смог захватить пакет
  }

  auto datalink = std::make_unique<DataLink>();
  auto network = std::make_unique<Network>();

  datalink->deserializeHeader(bytes);
  network->deserializeHeader(bytes);

  if (network->isHeaderEmpty()) {
    return;
  }

  auto transport = TransportFactory::makeTransport(network->getProtocol());
  transport->deserializeHeader(
      bytes, datalink->getHeaderSize() + network->getHeaderSize());

  Packet packet;
  QDateTime time;
  time.setSecsSinceEpoch(header->ts.tv_sec);

  packet.number = m_packetCount;
  packet.fullData = datalink->getFullData() + network->getFullData() +
                    transport->getFullData();
  packet.timestamp = time.time();
  packet.sourceIp = network->getSourceIp();
  packet.destIp = network->getDestIp();
  packet.protocol = network->getProtocolName();
  packet.length = QString::number(header->len);

  m_packetCount++;
  emit packetDeserialized(packet);
}

void Sniffer::stopCapture() {
  m_running = false;
}

Sniffer::~Sniffer() {
  m_running = false;
}
