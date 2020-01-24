import QtQuick 2.0
import gameboard.data 1.0

GridView {
    id: view
    cellWidth: width/4
    cellHeight: height/4
    model: GameBoardData { }
    delegate: Item {
        width: view.cellWidth
        height: view.cellHeight
        Square {
            anchors.fill: parent
            visible: view.model.hiddenElement !== display
        }
    }

}



