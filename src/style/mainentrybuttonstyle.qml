import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

QPushButton {
        id: button
        text: "Button"
        backgroundColor: "rgb(225, 225, 225)"
        border.color: "gray"
        border.width: 2
        border.radius: 10
        padding: 2
        borderStyle: Qt.OutsetBorder
        onHover: {
            backgroundColor: "rgb(229, 241, 251)"
            color: "black"
        }
        onPressed: {
            backgroundColor: "rgb(204, 228, 247)"
            borderStyle: Qt.InsetBorder
        }
    }
