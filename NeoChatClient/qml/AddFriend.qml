import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
  ColumnLayout {
      Label {
          text: "账号"
      }
      TextField {
          text: "Enter account"
      }
      Label {
          text: "邮箱"
      }
      TextField {
          text: "Enter email"
      }
      Button {
          onClicked: {

          }
      }
  }
}
