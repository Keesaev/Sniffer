import QtQuick 2.0
import QtCharts 2.3

Item {
    width: parent.width; height: parent.height / 2
    property int lastTime: (new Date()).getMinutes() * 60 + (new Date()).getSeconds()
    property int lastCount: 0

    function addPoint(){
        var date = new Date()
        var time = date.getMinutes() * 60 + date.getSeconds()
        if(time != lastTime){
            lineSeries.append(lastTime, lastCount)
            lastCount = 0
            lastTime = time
        }
        else
            lastCount++
    }

    ChartView{
        anchors.fill: parent
        antialiasing: true

        LineSeries {
            id: lineSeries

            axisX: ValueAxis {
                id: xAxis
                min: lastTime - 30
                max: lastTime + 30

            }
            axisY: ValueAxis{
                min: 0
                max: 100
            }
        }
    }
}
