import QtQuick
import QtMultimedia

Item {
    id: message
    width: 300
    height: parent.height
    property alias title: titleLabel.text
    Rectangle {
        anchors.fill: parent
        color: "black"
      Column {
        Rectangle {
          Text {
            id: titleLabel
            text: title
            color: "red"
          }
          color: "black"
          width: parent.width
          height: 20
          id: title
        }
        Rectangle {
          width: 200
          height: 150
          color:"blue"
          MediaPlayer {
            id: m_player
            source: "/home/aero/Videos/a.mp4"
            videoOutput: video_put
          }
          VideoOutput {
              id: video_put
              anchors.fill: parent
          }
          MouseArea {
              onClicked: {
                  console.log("play")
                  m_player.play()
              }
          }
        }
        Component.onCompleted: {
            m_player.play()
          console.log("message")
        }
      }
    }
}
