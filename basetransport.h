#ifndef BASETRANSPORT_H
#define BASETRANSPORT_H

#include <QObject>
#include <vector>

using namespace std;

class BaseTransport : public QObject
{
    Q_OBJECT
public:
    explicit BaseTransport(QObject *parent = nullptr);

    virtual void deserializeHeader(const u_char *bytes, int offset) = 0;

    virtual bool isHeaderInvalid() = 0;

    virtual QString getFullData() = 0;

    virtual ~BaseTransport(){}
signals:

};

#endif // BASETRANSPORT_H
