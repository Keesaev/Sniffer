#include "packet_model.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QScopedPointer>

int PacketModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)
  return m_packets.length();
}

QVariant PacketModel::data(const QModelIndex& index, int role) const {
  switch (role) {
    case NumberRole:
      return m_packets.at(index.row()).number;
    case SourceIpRole:
      return m_packets.at(index.row()).sourceIp;
    case DestIpRole:
      return m_packets.at(index.row()).destIp;
    case ProtocolRole:
      return m_packets.at(index.row()).protocol;
    case LengthRole:
      return m_packets.at(index.row()).length;
    case FullDataRole:
      return m_packets.at(index.row()).fullData;
    case TimestampRole:
      return m_packets.at(index.row()).timestamp;
    default:
      return data(index, role);
  }
}

QHash<int, QByteArray> PacketModel::roleNames() const {
  return QHash<int, QByteArray>{
      {NumberRole, "number"},      {SourceIpRole, "sourceIp"},
      {DestIpRole, "destIp"},      {ProtocolRole, "protocol"},
      {LengthRole, "length"},      {FullDataRole, "fullData"},
      {TimestampRole, "timestamp"}};
}

void PacketModel::clear() {
  beginResetModel();
  m_packets.clear();
  endResetModel();
}

void PacketModel::addPacket(const Packet p) {
  beginInsertRows(QModelIndex(), m_packets.size(), m_packets.size());
  m_packets.push_back(p);
  endInsertRows();
}

QVariantMap PacketModel::get(int row) {
  QHash<int, QByteArray> names = roleNames();
  QHashIterator<int, QByteArray> i(names);
  QVariantMap res;
  while (i.hasNext()) {
    i.next();
    QModelIndex idx = index(row, 0);
    QVariant v = idx.data(i.key());
    res[i.value()] = v;
  }
  return res;
}

int PacketModel::count() {
  return m_packets.size();
}

void PacketModel::save() {
  QScopedPointer<QWidget> widget(new QWidget());
  QString fileName = QFileDialog::getSaveFileName(
      widget.get(), tr("Сохранить файл"), "", tr("Text files (*.txt)"));
  if (fileName.isEmpty())
    return;
  if (!fileName.endsWith(".txt"))
    fileName += ".txt";
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Couldn't open file";
    return;
  }
  QDataStream stream(&file);

  foreach (const Packet& packet, m_packets) {
    stream << packet.number << packet.sourceIp << packet.destIp
           << packet.protocol << packet.length << packet.fullData
           << packet.timestamp;
  }
  file.close();
}

void PacketModel::load() {
  QScopedPointer<QWidget> widget(new QWidget());
  QString fileName = QFileDialog::getOpenFileName(
      widget.get(), tr("Открыть файл"), "", tr("Text files (*.txt)"));
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Couldn't open file";
    return;
  }
  QDataStream stream(&file);

  beginResetModel();
  m_packets.clear();
  while (!stream.atEnd()) {
    Packet i;
    stream >> i.number >> i.sourceIp >> i.destIp >> i.protocol >> i.length >>
        i.fullData >> i.timestamp;
    m_packets.push_back(i);
  }
  endResetModel();
  file.close();
}
