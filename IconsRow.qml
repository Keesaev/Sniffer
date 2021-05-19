import QtQuick 2.15

Row{
    leftPadding: 10; topPadding: 10; bottomPadding: 10; rightPadding: 10
    spacing: 5

    signal startPressed()
    signal stopPressed()
    signal backPressed()

    property bool running: false

    property string startImg: "Images/Icons/play.png"
    property string startHoveredImg: "Images/Icons/play_hovered.png"
    property string stopImg: "Images/Icons/stop.png"
    property string stopHoveredImg: "Images/Icons/stop_hovered.png"
    property string backImg: "Images/Icons/back.png"
    property string backHoveredImg: "Images/Icons/back_hovered.png"

    Image {
        id: startStopBtn
        property string startStopSrc: startImg
        source: startStopSrc
        width: 30; height: 30

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(running){
                    startStopBtn.startStopSrc = stopImg
                    stopPressed()
                    running = false
                }
                else{
                    startStopBtn.startStopSrc = startImg
                    startPressed()
                    running = true
                }
            }
            onEntered: {
                if(running)
                    startStopBtn.startStopSrc = stopHoveredImg
                else
                    startStopBtn.startStopSrc = startHoveredImg
            }
            onExited: {
                if(running)
                    startStopBtn.startStopSrc = stopImg
                else
                    startStopBtn.startStopSrc = startImg
            }
        }
    }
    Image{
        id: backBtn
        property string backSrc: backImg
        source: backSrc
        width: 30; height: 30

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                backPressed()
            }
            onEntered: {
                backBtn.backSrc = backHoveredImg
            }
            onExited: {
                backBtn.backSrc = backImg
            }
        }
    }
}
