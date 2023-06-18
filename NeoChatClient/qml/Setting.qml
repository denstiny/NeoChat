import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: setting
    anchors.fill: parent
    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        color: "black"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                setting.destroy()
            }
        }
    }

    Rectangle {
        width: 200
        height: 300
        anchors.centerIn: parent
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            Rectangle {
                height: 100
                width: 100
                color: "red"
                Image {
                    anchors.fill: parent
                    id: user_icon
                    source: "file"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("更换头像")
                    }
                }
            }

            Label {
                id: username
            }

            TextField {
                id: user_info
                placeholderText: "个人简介"
            }

            TextField {
                id: user_name
                placeholderText: "名字"
            }

            TextField {
                id: user_phone
                placeholderText: "电话号码"
            }

            // 底部按钮
            RowLayout {
                spacing: 10
                Button {
                    text: "Save"
                    Layout.fillWidth: true
                }
                Button {
                    text: "Cancel"
                    Layout.fillWidth: true
                }
            }
        }
    }

}
