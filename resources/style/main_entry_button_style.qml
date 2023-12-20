import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "您的应用程序标题"

    Rectangle {
        anchors.fill: parent

        // 构建开始按钮
        Button {
            anchors {
                left: parent.left
                bottom: parent.bottom - parent.height / 4
            }
            background: Rectangle {
                color: "rgb(225, 225, 225)"
                radius: 10
            }
            contentItem: Text {
                color: "black"
                anchors.centerIn: parent
            }
            onPressed: {
                background.color = "rgb(204, 228, 247)"
            }
            onReleased: {
                background.color = "rgb(225, 225, 225)"
            }
            onHoveredChanged: {
                if (hovered) {
                    background.color = "rgb(229, 241, 251)"
                } else {
                    background.color = "rgb(225, 225, 225)"
                }
            }
        }
    }
}
