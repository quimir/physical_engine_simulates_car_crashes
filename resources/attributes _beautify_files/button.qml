import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Styled Button Example"

    Rectangle {
        width: 200
        height: 50
        color: "#e1e1e1"

        MouseArea {
            id: buttonArea
            anchors.fill: parent

            Rectangle {
                id: buttonRect
                anchors.fill: parent
                border.color: "gray"
                border.width: 2
                radius: 10

                color: buttonArea.pressed ? "#cce4f7" : (buttonArea.containsMouse ? "#e5f1fb" : "#e1e1e1")

                Text {
                    anchors.centerIn: parent
                    text: "按钮"
                    font.pixelSize: 16
                    color: buttonArea.pressed ? "black" : "black"
                }
            }
        }
    }
}
