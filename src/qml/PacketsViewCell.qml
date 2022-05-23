import QtQuick 2.12

Rectangle{
    property string cellText
    property real cellWidth: parent.width / 6
    property string cellColor: "white"

    function setCellText(s){
        cellText = s
    }

    width: cellWidth
    height: 20
    color: cellColor

    border.color: "grey"
    border.width: 1

    Text {
        text: cellText
        anchors.left: parent.left
        anchors.horizontalCenter: parent.horizontalCenter
        leftPadding: 10
    }
}
