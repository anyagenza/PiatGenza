import QtQuick 2.0

Rectangle {
    id: square
    radius: 5
    border.color: "black"
    border.width: 2
    color: "dimgrey"
    Text {
        id: delegateText
        text: model.display
        anchors.centerIn: parent
        color: "white"
        font {
            bold: (square.width + square.height)/4
            pointSize: 24
        }
    }
    Behavior on y {
                NumberAnimation { duration: 6000 }
            }

}
