#ifndef SNIFFERWRAPPER_H
#define SNIFFERWRAPPER_H

#include <qqml.h>
#include "sniffer.h"

#include <QObject>
#include <QThread>

class SnifferWrapper : public QObject {
  Q_OBJECT
  std::unique_ptr<Sniffer> m_sniffer;
  QThread m_thread;

  QString m_device;

 public:
  explicit SnifferWrapper(QObject* parent = nullptr);
  ~SnifferWrapper();

  Q_INVOKABLE bool startCapture();
  Q_INVOKABLE void stopCapture();
  Q_INVOKABLE QVariantMap getDevs();
  Q_INVOKABLE void setDev(QString const& dev);
  Q_INVOKABLE void closeHandle();
 signals:
  void packetDeserialized(const Packet packet);
};

#endif  // SNIFFERWRAPPER_H
