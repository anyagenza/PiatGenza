import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    id: window
    visible: true
    width: 640
    height: 480
    Rectangle {
        color: "dimgray"
        anchors.fill: parent
        GameBoard {
            id: gameboard
            y: window.height/6
            width: parent.width
            height: parent.height - overBoard.height
        }
        Rectangle {
            id: overBoard
            color: "dimgray"
            width: window.width
            height: window.height/6
                Button {
                    id: button
                    width: 100
                    height: window.height/10
                    anchors.centerIn: parent
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: gameboard.model.shuffle()
                    }
                    states: State {
                            name: "pressed"; when: mouseArea.pressed
                            PropertyChanges { target: button; scale: 1.2 }
                        }
                }
        }
    }


}
