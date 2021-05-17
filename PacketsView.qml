import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import PacketData 1.1

Window{
    id: packetsView
    width: 800
    height: 600
    visible: false

    function addPacketToView(packet){
        listModel.append({
                    number: packet.getNumber(),
                    timestamp: packet.getTimestamp(),
                    source: packet.getSourceIp(),
                    destination: packet.getDestIp(),
                    protocol: packet.getProtocol(),
                    length: packet.getLength(),
                    fullData: packet.getFullData()
                });
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


    }
}
