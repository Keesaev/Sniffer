#include "sniffer_wrapper.h"

SnifferWrapper::SnifferWrapper(QObject* parent) : QObject(parent) {
  connect(&m_sniffer, &Sniffer::packetDeserialized, this,
          &SnifferWrapper::packetDeserialized);
  connect(&m_thread, &QThread::started, &m_sniffer,
          &Sniffer::startLoopingCapture);
}

void SnifferWrapper::startCapture(int c) {
  m_sniffer.moveToThread(&m_thread);
  m_sniffer.setMaxPacket(c);
  m_thread.start();
}

void SnifferWrapper::stopCapture() {
  m_sniffer.stopCapture();
  m_thread.terminate();
}

void SnifferWrapper::setDev(QString const& d) {
  m_sniffer.setDev(d);
}

bool SnifferWrapper::initPcap() {
  return m_sniffer.initPcap();
}

QVariantMap SnifferWrapper::getDevs() {
  return m_sniffer.getDevs();
}

void SnifferWrapper::closeHandle() {
  m_sniffer.closeHandle();
  m_thread.quit();
  m_thread.wait();
}

SnifferWrapper::~SnifferWrapper() {
  closeHandle();
}
