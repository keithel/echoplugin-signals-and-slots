import QtQuick 2.7
import QtQuick.Controls 1.5 as Controls1
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import com.l3t.EchoPlugin 1.0

Controls1.ApplicationWindow {
    visible: true
    height: minimumHeight
    width: minimumWidth
    minimumHeight: 250
    minimumWidth: gridlayout.implicitWidth
    title: qsTr("Echo Window")

    property QtObject plugin: PluginManager.currentPlugin

    menuBar: Controls1.MenuBar {
        Controls1.Menu {
            title: qsTr("File")
            Controls1.MenuItem {
                text: qsTr("&Plugin")
                onTriggered: console.log("Choose Plugin action triggered");
            }
            Controls1.MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    GridLayout {
        id: gridlayout
        anchors.fill: parent
        anchors.margins: 5
        columns: 2
        ComboBox {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            anchors.horizontalCenter: parent.horizontalCenter
            model: PluginManager.pluginNames
            onCurrentTextChanged: {
                console.log("loading plugin " + currentText)
                PluginManager.loadPlugin(currentText);
                messageField.text = ""
            }
        }

        Label {
            text: "Message:"
        }
        TextField {
            id: messageField
            Layout.fillWidth: true
            onEditingFinished: echo()

            function echo() {
                answerField.text = plugin.echo(text);
            }
        }
        Label {
            text: "Answer:"
        }
        TextField {
            id: answerField
            Layout.fillWidth: true
            readOnly: true
        }
        Label {
            text: "Signaled Answer:"
        }
        TextField {
            id: signaledAnswerField
            Layout.fillWidth: true
            readOnly: true
            Connections {
                target: plugin
                onEchoSignal: signaledAnswerField.text = message
            }
        }
        Button {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            text: "Send Message"
            onPressed: messageField.echo()
        }
    }
}
