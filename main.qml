import QtQuick 2.12
import QtQuick.Window 2.12
import SnifferWrapper 1.1
import PacketData 1.1
import QtQuick.Controls 2.0

Window {

    id: mainView
    width: 640
    height: 480
    visible: true
    title: qsTr("Выберите устройство")
    property var devArray: snifferWrapper.getDevs()

    ListModel{
        id: listModel

        Component.onCompleted: {
            for(var i in devArray){
                listModel.append({name: i, description: devArray[i]})
            }
        }
    }

    Rectangle{
        id: textRect
        height: 30
        width: parent.width

        Text{
            text: "Выберите устройство для захвата:"
            leftPadding: 20
            topPadding: 10
        }
    }

    Rectangle{
        id: devsRect
        width: parent.width
        height: parent.height * 0.8
        anchors {
            top: textRect.bottom;
            left: parent.left;
            right: parent.right
        }

        ListView{
            id: listView
            anchors.fill: devsRect
            ScrollBar.vertical: ScrollBar{}

            leftMargin: 20
            rightMargin: 20
            topMargin: 20
            bottomMargin: 20
            spacing: 5

            model: listModel

            delegate: MouseArea{
                width: devsRect.width; height: 40
                onClicked: listView.currentIndex = index
                property string c: index == listView.currentIndex ? "lightblue" : "lightgrey"
                DevicesListDelegate{
                    rectColor: c
                }
            }
        }
    }


    Rectangle{
        id: buttonLine
        anchors {
            left: parent.left;
            right: parent.right;
            bottom: parent.bottom
        }
        height: 70
        width: parent.width

        Button{
            leftInset: 20
            topInset: 10
            leftPadding: 30
            topPadding: 15
            text: "Открыть файл"
        }

        Rectangle{
            anchors {
                right: parent.right
            }
            height: 70
            width: 235
            Row{
                leftPadding: 10
                topPadding: 10
                anchors.fill: parent
                spacing: 5
                Button{
                    text: "Oк"
                    onClicked: {

                        packetsView.show()
                        mainView.hide()

                    }
                }
                Button{
                    text: "Выход"
                    onClicked: {
                        Qt.quit()
                    }
                }
            }
        }
    }

    PacketsView{
        id: packetsView
        visible: false

        // Кнопки-иконки сверху
        IconsRow{
            id: iconsRow

            onPlayPressed: {
                snifferWrapper.setDev(listModel.get(listView.currentIndex).name)
                snifferWrapper.initPcap()
                snifferWrapper.startCapture(100)
            }
            onStopPressed: {
                snifferWrapper.stopCapture()
            }
        }
    }

    SnifferWrapper{
        id: snifferWrapper

        onPacketDeserialized: {
            packetsView.addPacketToView(packet)
        }
    }
}
