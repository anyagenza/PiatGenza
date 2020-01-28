import QtQuick 2.0

Rectangle {
    id: square
    radius: 5
    border.color: "black"
    border.width: 2
    color: "dimgrey"
    property alias text: delegateText.text

    Text {
        id: delegateText
        anchors.centerIn: parent
        color: "white"
        font {
            bold: (square.width + square.height) / 4
            pointSize: 24
        }
    }
    Behavior on y {
        NumberAnimation { duration: 6000 }
    }

}
