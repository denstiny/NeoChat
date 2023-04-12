import QtQuick

Item {
  id: loginDialog
  width: 300
  height: parent.height
  property alias title: titleLabel.text
  Column {
    Rectangle {
      Text {
        id: titleLabel
        text: title
      color: "blue"
      }
      width: parent.width
      height: 20
      id: title
    }
    Rectangle {
      width: 48
      height: 48
      color: "red"
      MouseArea{
          onClicked: {
              console.log("hello")
          }
      }
    }
  }
}
