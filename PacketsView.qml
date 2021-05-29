import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import PacketModel 1.1

Window {
     id: packetsView
     width: 1000
     height: 600
     visible: false

     property int totalPackets: 0

     signal startPressed()
     signal stopPressed()
     signal backPressed()

     function addPacketToView(packet){
         packetModel.addPacket(packet)
         totalPackets++
         protocolChart.appendSlice(packetModel.get(packetModel.count() - 1).protocol)
         timeChart.addPoint()
     }

     function start(){
         if(!iconsRow.running){
             totalPackets = 0
             protocolChart.clear()
             timeChart.clear()
             timeChart.start()
             packetsView.startPressed()
         }
     }

     function stop(){
         timeChart.stop()
         if(iconsRow.running)
            packetsView.stopPressed()
     }

     function save(){
         timeChart.stop()
         if(iconsRow.running)
             packetsView.stopPressed()
         iconsRow.setStopped()
         packetModel.save()
     }

     function open() {
         if(iconsRow.running)
             packetsView.stopPressed()
         iconsRow.setStopped()
         packetModel.load()
         protocolChart.clear()
         timeChart.stop()
         timeChart.clear()
         for(var i = 0; i < packetModel.count(); i++){
             protocolChart.appendSlice(packetModel.get(i).protocol)
         }
         totalPackets = packetModel.count()
     }

     function clearModel(){
         packetModel.clear()
         listView.currentIndex = -1
     }

     Rectangle {
        id: leftRect
        width: parent.width * 0.6; height: parent.height

        anchors{
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }

        Rectangle{
           id: topRect
           width: parent.width; height: parent.height * 0.7
           anchors{
               top: parent.top
               left: parent.left
               right: parent.right
           }

           // Ряд иконок
           IconsRow{
               id: iconsRow

               onStartPressed: {
                   start()
               }
               onStopPressed: {
                   stop()
               }
               onSavePressed: {
                   save()
               }
               onOpenPressed: {
                   open()
               }
               onBackPressed: {
                   totalPackets = 0
                   if(running)
                       packetsView.stopPressed()
                   iconsRow.setStopped()
                   clearModel()
                   protocolChart.clear()
                   timeChart.stop()
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
                   add: Transition {
                       NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 }
                       NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 200 }
                   }

                   populate: Transition {
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


        Rectangle {
            id: bottomRect
            width: parent.width; height: parent.height * 0.3

            anchors{
                top: topRect.bottom
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
    }

    // Диаграммы
    Rectangle {
        id: rightRect
        width: parent.width * 0.4; height: parent.height
        border { width: 1; color: "grey"}

        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: leftRect.right
        }

        Rectangle {
            width: parent.width; height: 20
            id: statsRect
            border.width: 1; border.color: "grey"
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            Text {
                anchors.centerIn: parent

                text: "Всего пакетов захвачено: " + totalPackets
            }
        }

        ProtocolChart{
            id: protocolChart
            anchors{
                left: parent.left
                right: parent.right
                top: statsRect.bottom
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

    PacketModel{
        id: packetModel
    }

    onClosing: {
        Qt.quit()
    }
}
