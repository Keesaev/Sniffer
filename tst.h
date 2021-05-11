#ifndef TST_H
#define TST_H

#include <QObject>
#include <string>
#include <vector>
#include <qqml.h>

using namespace std;

class Test : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Test(QObject *parent = nullptr);
    Q_INVOKABLE QVariantMap getList(){
        return map;
    }
    QVariantMap map = {{"a", "b"}, {"c", "d"}, {"e", "f"}};
signals:

};

#endif // TST_H
