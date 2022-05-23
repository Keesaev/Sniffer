#include "sniffer_wrapper.h"

SnifferWrapper::SnifferWrapper(QObject* parent) : QObject(parent) {}

bool SnifferWrapper::startCapture() {
  m_sniffer.reset(new Sniffer(m_device));

  if (!m_sniffer->isValid()) {
    qDebug() << "Could not start capture on " << m_device;
    return false;
  }

  connect(m_sniffer.get(), &Sniffer::packetDeserialized, this,
          &SnifferWrapper::packetDeserialized);
  connect(&m_thread, &QThread::started, m_sniffer.get(),
          &Sniffer::startCapture);

  m_sniffer->moveToThread(&m_thread);
  m_thread.start();

  return true;
}

void SnifferWrapper::stopCapture() {
  m_sniffer->stopCapture();
  m_thread.quit();
  m_thread.wait();
  m_sniffer.reset();
}

void SnifferWrapper::setDev(QString const& dev) {
  m_device = dev;
}

QVariantMap SnifferWrapper::getDevs() {
  QVariantMap d;
  pcap_if_t* alldevsp;
  char errbuf[PCAP_ERRBUF_SIZE];
  int retVal = pcap_findalldevs(&alldevsp, errbuf);

  if (retVal == PCAP_ERROR) {
    qDebug() << errbuf << "\n";
    return QVariantMap();
  } else {
    while (alldevsp->next != NULL) {
      QString desc = alldevsp->description;
      if (desc.isEmpty())
        desc = "Нет описания";
      d.insert(QString(alldevsp->name), desc);
      alldevsp = alldevsp->next;
    }
    return d;
  }
}

void SnifferWrapper::closeHandle() {
  if (m_sniffer)
    m_sniffer->stopCapture();

  m_thread.quit();
  m_thread.wait();
}

SnifferWrapper::~SnifferWrapper() {
  if (m_sniffer)
    m_sniffer->stopCapture();

  m_thread.quit();
  m_thread.wait();
}
