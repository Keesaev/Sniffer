// https://www.tcpdump.org/manpages/pcap.3pcap.html
// https://habr.com/ru/post/337840/

#include "sniffer.h"

Sniffer::Sniffer(QObject *parent) : QObject(parent) {}

// Возвращаем список доступных устройств
QVariantMap Sniffer::getDevs() {
  QVariantMap d;
  pcap_if_t *alldevsp;
  char errbuf[PCAP_ERRBUF_SIZE];
  int retVal = pcap_findalldevs(&alldevsp, errbuf);

  if (retVal == PCAP_ERROR) {
    qDebug() << __func__ << __LINE__ << errbuf << "\n";
    QVariantMap m;
    return m;
  } else {
    while (alldevsp->next != NULL) {
      QString desc = alldevsp->description;
      if (desc.isEmpty()) desc = "Нет описания";
      d.insert(QString(alldevsp->name), desc);
      alldevsp = alldevsp->next;
    }
    return d;
  }
}

// Устройство для прослушивания устанавливается извне
void Sniffer::setDev(QString d) {
  QByteArray ba = d.toLocal8Bit();
  char *devName = ba.data();
  m_dev = devName;
}

// Инициализация pcap
bool Sniffer::initPcap() {
  if (m_dev == NULL) {
    qDebug() << __func__ << __LINE__ << "m_dev = NULL";
    return false;
  }
  char errbuf[PCAP_ERRBUF_SIZE];
  m_handle = pcap_create(m_dev, errbuf);
  if (m_handle == NULL) {
    qDebug() << __func__ << __LINE__ << errbuf;
    return false;
  } else {
    pcap_set_snaplen(m_handle, 65535);
    pcap_set_promisc(m_handle, 1);
    pcap_set_rfmon(m_handle, 0);
    pcap_set_timeout(m_handle, 1000);
    pcap_set_immediate_mode(m_handle, 1);
    pcap_set_buffer_size(m_handle, PCAP_BUF_SIZE);
    pcap_set_tstamp_type(m_handle, PCAP_TSTAMP_HOST);
    int retVal = pcap_activate(m_handle);
    if (retVal >= 0) {
      return true;
    } else {
      qDebug() << __func__ << __LINE__ << retVal;
      pcap_close(m_handle);
      return false;
    }
  }
}

// Вызываем captureSinglePacket в цикле, контроллируем его
// переменной m_running
void Sniffer::startLoopingCapture() {
  m_running = true;
  m_packetCount = 1;  // NOTE: пока убрал
  if (m_maxPacket == -1) {
    while (m_running) {
      captureSinglePacket();
    }
  } else {
    while (m_maxPacket-- && m_running) {
      captureSinglePacket();
    }
  }
}

// Захватываем один пакет и издаем сигнал
void Sniffer::captureSinglePacket() {
  pcap_pkthdr *header;
  const u_char *bytes;
  int retVal = pcap_next_ex(m_handle, &header, &bytes);
  if (retVal != 1) {
    return;  // PCAP не смог захватить пакет
  }

  DataLink *datalink = new DataLink();
  Network *network = new Network();
  BaseTransport *transport;

  datalink->deserializeHeader(bytes);
  network->deserializeHeader(bytes);
  if (network->isHeaderEmpty()) {
    delete datalink;
    delete network;
    return;
  }

  transport = Factory::makeTransport(network->getProtocol());
  transport->deserializeHeader(
      bytes, datalink->getHeaderSize() + network->getHeaderSize());

  Packet packet;
  QDateTime time;
  // time.setTime_t(header->ts.tv_sec);
  time.setSecsSinceEpoch(header->ts.tv_sec);

  packet.number = m_packetCount;
  packet.fullData = datalink->getFullData() + network->getFullData() +
                    transport->getFullData();
  packet.timestamp = time.time();
  packet.sourceIp = network->getSourceIp();
  packet.destIp = network->getDestIp();
  packet.protocol = network->getProtocolName();
  packet.length = QString::number(header->len);

  emit packetDeserialized(packet);

  m_packetCount++;
  delete datalink;
  delete network;
  delete transport;
}

void Sniffer::stopCapture() { m_running = false; }

void Sniffer::setMaxPacket(int c) { m_maxPacket = c; }

void Sniffer::closeHandle() {
  m_running = false;
  pcap_close(m_handle);
}
