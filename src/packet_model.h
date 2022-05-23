#ifndef PACKETMODEL_H
#define PACKETMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "packet.hpp"

class PacketModel : public QAbstractListModel {
  Q_OBJECT
  QList<Packet> m_packets;
  enum Roles {
    NumberRole = Qt::UserRole,
    SourceIpRole,
    DestIpRole,
    ProtocolRole,
    LengthRole,
    FullDataRole,
    TimestampRole
  };

 public:
  virtual int rowCount(const QModelIndex& parent) const final;
  virtual QVariant data(const QModelIndex& index, int role) const final;
  virtual QHash<int, QByteArray> roleNames() const final;

  Q_INVOKABLE void clear();
  Q_INVOKABLE void addPacket(const Packet p);
  Q_INVOKABLE QVariantMap get(int row);
  Q_INVOKABLE int count();
  Q_INVOKABLE void save();
  Q_INVOKABLE void load();
};

#endif  // PACKETMODEL_H
