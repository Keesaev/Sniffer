QT += core widgets quick

CONFIG += c++11 charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        basetransport.cpp \
        datalink.cpp \
        factory.cpp \
        icmp.cpp \
        main.cpp \
        network.cpp \
        packetdata.cpp \
        packetmodel.cpp \
        sniffer.cpp \
        snifferwrapper.cpp \
        tcp.cpp \
        testpacket.cpp \
        tst.cpp \
        udp.cpp \
        unknowntransport.cpp

RESOURCES += qml.qrc

LIBS += -lpcap

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    basetransport.h \
    datalink.h \
    factory.h \
    icmp.h \
    network.h \
    packetdata.h \
    packetmodel.h \
    sniffer.h \
    snifferwrapper.h \
    tcp.h \
    testpacket.h \
    tst.h \
    udp.h \
    unknowntransport.h
