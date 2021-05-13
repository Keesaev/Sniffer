import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Window{
    id: packetsView
    width: 640
    height: 480
    visible: false

    // Кнопки-иконки сверху
    Row{
        id: iconsRow
        leftPadding: 10; topPadding: 10; bottomPadding: 10; rightPadding: 10
        spacing: 5
        Image{
            source: "Images/Play.png"
            width: 30; height: 30

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    // Start
                }
            }
        }
        Image{
            source: "Images/Stop.png"
            width: 30; height: 30

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.quit()
                    // Stop
                }
            }
        }
    }

    // Заголовок таблицы
    PacketsViewHeader{
        id: headerRect
        width: parent.width; height: 20
        anchors{
            top: iconsRow.bottom
            left: parent.left
            right: parent.right
        }
    }

    // Таблица с пакетами
    Rectangle{
        id: packetsRect
        width: parent.width; height: parent.height
        anchors {
            top: headerRect.bottom;
            left: parent.left;
            right: parent.right
            bottom: fullDataRect.top
        }

        ListView{
            id: listView
            anchors.fill: packetsRect
            width: parent.width; height: parent.height

            clip: true
            ScrollBar.vertical: ScrollBar{}

            model: listModel

            delegate: MouseArea{
                width: packetsRect.width; height: 20
                onClicked: {
                    listView.currentIndex = index
                }
                property string rowColor: index == listView.currentIndex ? "lightblue" : "white"

                Row{
                    height: 20; width: parent.width
                    PacketsViewCell { cellText: number; cellWidth: parent.width / 10; cellColor: rowColor }
                    PacketsViewCell { cellText: timestamp; cellWidth: parent.width / 4; cellColor: rowColor }
                    PacketsViewCell { cellText: source; cellColor: rowColor }
                    PacketsViewCell { cellText: destination; cellColor: rowColor }
                    PacketsViewCell { cellText: protocol; cellColor: rowColor }
                    PacketsViewCell { cellText: length; cellWidth: parent.width; cellColor: rowColor }
                }
            }

            onCurrentIndexChanged: {
                console.log(currentIndex)
            }
        }
    }

    // Область с описанием выбранного пакета
    Rectangle{
        id: fullDataRect
        width: parent.width; height: parent.height / 3
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        border{ width: 1; color: "grey" }

        ScrollView{
            anchors.fill: parent
            clip: true

            Text{
                padding: {left: 5}
                text: listModel.get(listView.currentIndex).fullData
            }
        }
    }

    ListModel{
        id: listModel
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\n\n\n\BlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla\nBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }

        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
        ListElement{
            number: 1
            timestamp: "00.00.01"
            source: "192.168.1.1"
            destination: "192.168.1.1"
            protocol: "TCP"
            length: 32
            fullData: "BlaBla"
        }
    }
}
