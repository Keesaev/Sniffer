QT += qml core gui widgets quick

CONFIG += c++17 charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(src/protocols/protocols.pri)

QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"

SOURCES += \
        src/main.cpp \
        src/packet_model.cpp \
        src/sniffer.cpp \
        src/sniffer_wrapper.cpp \
        src/transport_factory.cpp

RESOURCES += src/qml.qrc

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
    src/transport_factory.h \
    src/packet.hpp \
    src/packet_model.h \
    src/sniffer.h \
    src/sniffer_wrapper.h
