import QtQuick 2.0

Rectangle {
    id: cellP
    height: view.cellWidth
    width: view.cellHeight
    radius: 5
    border.color: "black"
    border.width: 1
    color: "lightpink"
    Text {
        text: index
        anchors.centerIn: parent
        font {
            bold: (cellP.width + cellP.height)/4
            pointSize: 24
        }
    }

}
