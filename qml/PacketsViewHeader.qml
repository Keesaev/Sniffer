import QtQuick 2.12

Row{
    height: parent.height
    width: parent.width

    PacketsViewCell { cellText: "№"; cellWidth: parent.width / 10 }
    PacketsViewCell { cellText: "Timestamp"; cellWidth: parent.width / 4 }
    PacketsViewCell { cellText: "Source" }
    PacketsViewCell { cellText: "Destination" }
    PacketsViewCell { cellText: "Protocol" }
    PacketsViewCell { cellText: "Size"; cellWidth: parent.width }
}
