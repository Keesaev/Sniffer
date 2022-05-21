QT += qml core gui widgets quick

CONFIG += c++17 charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(protocols/protocols.pri)

QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"

SOURCES += \
        main.cpp \
        packet_model.cpp \
        sniffer.cpp \
        sniffer_wrapper.cpp \
        transport_factory.cpp

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
    transport_factory.h \
    packet.hpp \
    packet_model.h \
    sniffer.h \
    sniffer_wrapper.h
