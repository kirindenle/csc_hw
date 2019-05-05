import QtQuick 2.12
//import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import OceanTableModel 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 760
    height: 810
    minimumWidth: 475
    minimumHeight: 300

    color: "#09102B"
    title: qsTr("Ocean simulation")

    TableView {
        id: tableView
        anchors.fill: parent

        rowSpacing: 1
        columnSpacing: 1

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}

        delegate: Rectangle {
            id: cell
            implicitWidth: 15
            implicitHeight: 15

            color: model.color
        }

        model: oceanTableModel

        contentX: (contentWidth - width) / 2;
        contentY: (contentHeight - height) / 2;
    }

    footer: Rectangle {
        signal nextStep

        id: footer
        height: 50
        color: "#F3F3F4"

        RowLayout {
            anchors.centerIn: parent

            Button {
                text: qsTr("Next")
                onClicked:
                {
                    oceanTableModel.nextStep();
                }
            }

            Item {
                width: 50
            }

            Slider {
                id: slider
                x: 245
                y: 17
                from: 0
                to: 1
                value: 0.9
            }

            Button {
                text: timer.running ? "❙❙" : "▶️"
                onClicked: timer.running = !timer.running
            }
        }

        Timer {
            id: timer
            interval: 1000 - (980 * slider.value)
            running: false
            repeat: true

            onTriggered: {
                oceanTableModel.nextStep();
            }
        }
    }

    Component.onCompleted: {
    }
}
