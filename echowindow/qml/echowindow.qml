import QtQuick 2.7
import QtQuick.Controls 1.5 as Controls1
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import com.l3t.EchoPlugin 1.0

Controls1.ApplicationWindow {
    visible: true
    height: 300
    width: 400
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("Echo Window")

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

    Column {
        anchors.fill: parent

        ComboBox {
            anchors.horizontalCenter: parent.horizontalCenter
            model: PluginManager.pluginNames
            onCurrentTextChanged: PluginManager.loadPlugin(currentText);
        }

        GridLayout {
            columns: 2
            Label {
                text: "Message:"
            }
            TextField {
                id: messageField
                onTextChanged: {
                    var plugin = PluginManager.currentPlugin(); // Can't do this! currentPlugin isn't a QObject derived thing!
                    answerField.text = plugin.echo(text);
                }
            }
            Label {
                text: "Answer:"
            }
            TextField {
                id: answerField
                enabled: false
            }
            Label {
                text: "Signaled Answer:"
            }
            TextField {
                id: signaledAnswerField
                enabled: false
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Echo plugin example")
        }
    }
}
