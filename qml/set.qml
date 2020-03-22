import QtQuick 2.0
import QtQuick.Controls 2.13

Item {
    Text {
        id: element
        x: 32
        y: 27
        text: qsTr("Функционал")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 25
    }

    CheckBox {
        id: checkBox
        x: 39
        y: 68
        width: 137
        height: 42
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox1
        x: 39
        y: 116
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox2
        x: 39
        y: 162
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox3
        x: 39
        y: 208
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox4
        x: 39
        y: 275
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox5
        x: 39
        y: 321
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox6
        x: 39
        y: 367
        text: qsTr("Check Box")
    }

    CheckBox {
        id: checkBox7
        x: 39
        y: 241
        text: qsTr("Check Box")
    }

}
