import QtQuick 2.0
import QtQuick.Window 2.14
import gameboard.data 1.0

GridView {
    id: view
    cellWidth: width / 4
    cellHeight: height / 4

    model: GameBoardData {
        onWinGame: messageLoader.source = "Message.qml";
    }

    delegate: Item {
        width: view.cellWidth
        height: view.cellHeight

        Square {
            id: currTile
            text: model.display
            anchors.fill: parent
            visible: view.model.hiddenElement !== display
        }

        MouseArea {
            id: mousearea
            anchors.fill: parent
            onClicked: view.model.move(index)
        }
    }
    move: Transition {

        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
    }

    Loader {
        anchors.fill: parent
        id: messageLoader
    }
}
