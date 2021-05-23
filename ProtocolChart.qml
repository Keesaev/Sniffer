import QtQuick 2.0
import QtCharts 2.3

Item {
    width: parent.width; height: parent.height / 2

    function appendSlice(a){
        if(pieSeries.find(a) == null){
            pieSeries.append(a, 1);
        }
        else
        {
            pieSeries.find(a).value++
        }
    }

    function clearPie(){
        pieSeries.clear()
    }

    ChartView {
        title: "Протоколы сетевого уровня"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        PieSeries{
            id: pieSeries
        }
    }
}
