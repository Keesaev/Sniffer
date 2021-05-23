#ifndef PACKETMODEL_H
#define PACKETMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDataStream>
#include <QFile>
#include <packetdata.h>

class PacketModel : public QAbstractListModel
{
    Q_OBJECT
    QList<PacketData> m_packets;
    enum Roles {
        NumberRole = Qt::UserRole,
        SourceIpRole, DestIpRole, ProtocolRole,
        LengthRole, FullDataRole, TimestampRole
    };

public:
    PacketModel();

    int rowCount(const QModelIndex &parent) const {
        return m_packets.length();
    }

    QVariant data(const QModelIndex &index, int role) const {
        auto packetsIndex = index.row();
        const PacketData &p = m_packets.at(packetsIndex);
        switch(role){
            case NumberRole:
                return p.number;
            case SourceIpRole:
                return p.sourceIp;
            case DestIpRole:
                return p.destIp;
            case ProtocolRole:
                return p.protocol;
            case LengthRole:
                return p.length;
            case FullDataRole:
                return p.fullData;
            case TimestampRole:
                return p.timestamp;
            default:
                return data(index, role);
        }
    }

    QHash<int, QByteArray> roleNames() const {
        return QHash<int, QByteArray> {
            { NumberRole, "number" },
            { SourceIpRole, "sourceIp" },
            { DestIpRole, "destIp" },
            { ProtocolRole, "protocol" },
            { LengthRole, "length" },
            { FullDataRole, "fullData" },
            { TimestampRole, "timestamp" }
        };
    }

    Q_INVOKABLE void clear(){
        beginResetModel();
        m_packets.clear();
        endResetModel();
    }

    Q_INVOKABLE void addPacket(const PacketData p){
        beginInsertRows(QModelIndex(), m_packets.size(), m_packets.size());
        m_packets.push_back(p);
        endInsertRows();
    }

    Q_INVOKABLE QVariantMap get(int row){
        QHash<int, QByteArray> names = roleNames();
        QHashIterator<int, QByteArray> i(names);
        QVariantMap res;
        while(i.hasNext()){
            i.next();
            QModelIndex idx = index(row, 0);
            QVariant v = idx.data(i.key());
            res[i.value()] = v;
        }
        return res;
    }

    Q_INVOKABLE int count(){
        return m_packets.size();
    }
};

#endif // PACKETMODEL_H
