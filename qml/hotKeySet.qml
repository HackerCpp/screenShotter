import QtQuick 2.9

Item {
    visible: true
    width: 400
    height: 400
    Text {
        id: element
        x: 32
        y: 27
        width: 122
        height: 25
        text: qsTr("Основные")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 25
    }

    Text {
        id: element1
        x: 38
        y: 70
        width: 85
        height: 17
        text: qsTr("Ctrl + Print")
        font.family: "Tahoma"
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element2
        x: 38
        y: 100
        width: 138
        height: 17
        text: qsTr("Ctrl + Shift + Print")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element3
        x: 38
        y: 130
        width: 84
        height: 17
        text: qsTr("Shift + Print")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element4
        x: 32
        y: 164
        height: 26
        text: qsTr("Вспомогательные")
        font.family: "Times New Roman"
        font.bold: true
        font.pixelSize: 25
    }

    Text {
        id: element5
        x: 113
        y: 70
        height: 18
        text: qsTr("- фрагмент экрана")
        font.pixelSize: 12
    }

    Text {
        id: element6
        x: 162
        y: 100
        height: 17
        text: qsTr("- Снимок экрана целиком")
        font.pixelSize: 12
    }

    Text {
        id: element7
        x: 123
        y: 130
        height: 17
        text: qsTr("- быстрый снимок")
        font.pixelSize: 12
    }

    Text {
        id: element8
        x: 38
        y: 278
        width: 51
        height: 17
        text: qsTr("Ctrl + S")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element9
        x: 38
        y: 313
        width: 25
        height: 17
        text: qsTr("Esc")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element10
        x: 38
        y: 243
        width: 54
        height: 17
        text: qsTr("Ctrl + C")
        font.bold: true
        font.family: "Tahoma"
        font.pixelSize: 12
    }

    Text {
        id: element11
        x: 38
        y: 208
        height: 17
        text: qsTr("Ctrl + Enter")
        font.bold: true
        font.pixelSize: 12
    }

    Text {
        id: element12
        x: 116
        y: 208
        height: 17
        text: qsTr("- отправить скриншот в хранилище")
        font.pixelSize: 12
    }

    Text {
        id: element13
        x: 92
        y: 243
        height: 17
        text: qsTr("- скопирывать скриншот в буфер обмена")
        font.pixelSize: 12
    }

    Text {
        id: element14
        x: 69
        y: 313
        height: 17
        text: qsTr("- отменить снятие скриншота")
        font.pixelSize: 12
    }

    Text {
        id: element15
        x: 92
        y: 278
        height: 17
        text: qsTr("- сохранить скриншот на компьютер")
        font.pixelSize: 12
    }
}
