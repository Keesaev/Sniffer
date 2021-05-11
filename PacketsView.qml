import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.qmlmodels 1.0

Window{
    id: packetsView
    width: 640
    height: 480
    visible: false

    Row{
        id: iconsRow
        leftPadding: 10
        topPadding: 10
        bottomPadding: 10
        rightPadding: 10
        spacing: 5
        Image{
            source: "Images/Play.png"
            width: 30
            height: 30

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    // Start
                }
            }
        }
        Image{
            source: "Images/Stop.png"
            width: 30
            height: 30

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    // Stop
                }
            }
        }
    }

    TableView{

        width: packetsView.width
        height: packetsView.height

        anchors {
            top: iconsRow.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: tableModel
        delegate: Rectangle{
            implicitHeight: 30
            implicitWidth: packetsView.width / 2
            border.width: 1

            Text{
                text: display
                anchors.centerIn: parent
            }
        }
    }

    TableModel{
        id: tableModel
        TableModelColumn { display: "name" }
        TableModelColumn { display: "description" }

        rows:[
            {
                "name" : "name1",
                "description" : "description1"
            },
            {
                "name" : "name1",
                "description" : "description1"
            },
            {
                "name" : "name1",
                "description" : "description1"
            }
        ]
    }
}
