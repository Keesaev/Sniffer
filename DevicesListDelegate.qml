import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.0

Rectangle{
    id: devicesListDelegate
    height: 40
    width: parent.width - 40
    property var rectColor: "lightgrey"
    color: rectColor

    Text{
        leftPadding: 50

        anchors {
            left: parent.left;
            verticalCenter: parent.verticalCenter
        }
        text: name
    }
    Text{
        anchors {
            left: parent.horizontalCenter;
            verticalCenter: parent.verticalCenter
        }
        text: description
    }

}
