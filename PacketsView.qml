import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import PacketModel 1.1

Window{
    id: packetsView
    width: 1000
    height: 600
    visible: false

    signal startPressed()
    signal stopPressed()
    signal backPressed()

    function addPacketToView(packet){
        packetModel.addPacket(packet)
        protocolChart.appendSlice(packetModel.get(packetModel.count() - 1).protocol)
        timeChart.addPoint()
    }

    function clearModel(){
        packetModel.clear()
        listView.currentIndex = -1
    }

    Rectangle{
       id: topRect
       width: parent.width; height: parent.height * 0.7

       anchors{
           left: parent.left
           right: parent.right
           top: parent.top
           bottom: bottomRect.top
       }

       Rectangle{
           id: leftRect
           width: topRect.width * 0.7; height: topRect.height
           anchors{
               left: topRect.left
               top: topRect.top
               bottom: topRect.bottom
           }

           // Ряд иконок
           IconsRow{
               id: iconsRow

               onStartPressed: {
                   if(!running){
                       protocolChart.clearPie()
                       packetsView.startPressed()
                   }
               }
               onStopPressed: {
                   if(iconsRow.running)
                      packetsView.stopPressed()
               }
               onSavePressed: {
                   if(iconsRow.running)
                       packetsView.stopPressed()
                   iconsRow.setStopped()
                   packetModel.save()
               }
               onOpenPressed: {
                   if(iconsRow.running)
                       packetsView.stopPressed()
                   iconsRow.setStopped()
                   packetModel.load()
               }
               onBackPressed: {
                   if(running)
                       packetsView.stopPressed()
                   iconsRow.setStopped()
                   clearModel()
                   packetsView.backPressed()
               }
           }

           // Заголовок таблицы
           PacketsViewHeader {
               id: headerRect
               width: parent.width; height: 20
               anchors {
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
                   bottom: parent.bottom
               }

               ListView{
                   id: listView
                   anchors.fill: packetsRect
                   width: parent.width; height: parent.height
                   clip: true
                   ScrollBar.vertical: ScrollBar{}
                   model: packetModel

                   // Анимации
                   add: Transition{
                       NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 }
                       NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 200 }
                   }

                   delegate: MouseArea{
                       width: packetsRect.width; height: 20
                       onClicked: {
                           listView.currentIndex = index
                       }
                       property string rowColor: index == listView.currentIndex ? "lightblue" : "white"

                       Row{
                           height: 20; width: parent.width
                           PacketsViewCell { cellText: number; cellWidth: parent.width / 10; cellColor: rowColor }
                           PacketsViewCell { cellText: Qt.formatTime(timestamp, "hh:mm:ss"); cellWidth: parent.width / 4; cellColor: rowColor }
                           PacketsViewCell { cellText: sourceIp; cellColor: rowColor }
                           PacketsViewCell { cellText: destIp; cellColor: rowColor }
                           PacketsViewCell { cellText: protocol; cellColor: rowColor }
                           PacketsViewCell { cellText: length; cellWidth: parent.width; cellColor: rowColor }
                       }
                   }
               }
           }
       }

        // Диаграммы
        Rectangle{
            id: rightRect
            width: topRect.width * 0.3; height: topRect.height
            border { width: 1; color: "grey"}

            anchors{
                left: leftRect.right
                right: topRect.right
                top: topRect.top
                bottom: topRect.bottom
            }

            ProtocolChart{
                id: protocolChart
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }
            }

            TimeChart{
                id: timeChart
                anchors {
                    left: parent.left
                    right: parent.right
                    top: protocolChart.bottom
                    bottom: parent.bottom
                }
            }
        }
    }

    Rectangle{
        id: bottomRect
        width: parent.width; height: parent.height * 0.3

        anchors{
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        // Область с описанием выбранного пакета
        Rectangle{
            id: fullDataRect
            width: parent.width; height: parent.height
            anchors {
                fill: parent
            }
            border{ width: 1; color: "grey" }

            ScrollView{
                anchors.fill: parent
                clip: true

                Text{
                    padding: { left: 5}
                    text: listView.currentIndex > -1 ? packetModel.get(listView.currentIndex).fullData : ""
                }
            }
        }
    }

    PacketModel{
        id: packetModel
    }
}
