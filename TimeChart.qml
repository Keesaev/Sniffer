import QtQuick 2.0
import QtCharts 2.3
import QtQuick.Controls 2.12

Item {
    width: parent.width; height: parent.height / 2
    property int time
    property int count
    property var startTime

    function start(){
        startTime = new Date()
        lineSeries.clear()
        time = 0
        count = 0
        chartView.yMax = 10
        chartView.xMin = 1
        chartView.xMax = 30
        timer.start()
    }

    function stop(){
        timer.stop()
    }

    function addPoint(){
        count++
    }

    function clear() {
        lineSeries.clear()
    }

    Timer {
        id: timer
        interval: 1000; running: false; repeat: true
        onTriggered: {
            if(count > chartView.yMax)
                chartView.yMax = count + 1
            if(time >= chartView.xMax)
            {
                chartView.xMax++
                chartView.xMin++
            }
            lineSeries.append(time, count)
            time++
            count = 0
        }
    }

    ChartView{
        id: chartView
        legend.visible: false
        anchors.fill: parent
        antialiasing: true
        property int yMax: 10
        property int xMin: 1
        property int xMax: 30

        ToolTip {
            id: toolTip
            width: 100
        }

        LineSeries {
            id: lineSeries

            axisX: ValueAxis {
                id: xAxis
                min: chartView.xMin
                max: chartView.xMax
                labelFormat: "%i"
            }
            axisY: ValueAxis{
                id: yAxis
                min: 0
                max: chartView.yMax
                labelFormat: "%i"
            }

            onHovered: {
                var timeVal = startTime.getTime() + point.x * 1000
                var newTime = new Date(timeVal)
                toolTip.show(qsTr("%1, %2".arg(newTime.toLocaleTimeString()).arg(parseInt(point.y))), 1000)
            }
        }
    }
}
