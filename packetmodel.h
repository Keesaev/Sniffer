#ifndef PACKETMODEL_H
#define PACKETMODEL_H

#include <QAbstractListModel>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QScopedPointer>

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
  PacketModel();

  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  QHash<int, QByteArray> roleNames() const;

  Q_INVOKABLE void clear();
  Q_INVOKABLE void addPacket(const Packet p);
  Q_INVOKABLE QVariantMap get(int row);
  Q_INVOKABLE int count();
  Q_INVOKABLE void save();
  Q_INVOKABLE void load();
};

#endif  // PACKETMODEL_H
