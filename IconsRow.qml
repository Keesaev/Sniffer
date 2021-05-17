import QtQuick 2.12


Row{
    leftPadding: 10; topPadding: 10; bottomPadding: 10; rightPadding: 10
    spacing: 5

    signal playPressed()
    signal stopPressed()

    Image{
        source: "Images/Play.png"
        width: 30; height: 30

        MouseArea{
            anchors.fill: parent
            onClicked: {
                playPressed()
            }
        }
    }
    Image{
        source: "Images/Stop.png"
        width: 30; height: 30

        MouseArea{
            anchors.fill: parent
            onClicked: {
                stopPressed()
            }
        }
    }
}
