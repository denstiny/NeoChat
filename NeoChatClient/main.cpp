#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


int main (int argc, char* argv[]) {
  QGuiApplication app (argc, argv);
  
  QQmlApplicationEngine engine;
  const QUrl url (u"qrc:/NeoChatClient/Main.qml"_qs);
  QObject::connect (&engine, &QQmlApplicationEngine::objectCreationFailed,
  &app, []() { QCoreApplication::exit (-1); },
  Qt::QueuedConnection);
  //    qDebug() << "RESOURES: " << RESOURES;
  engine.rootContext()->setContextProperty ("RES",
      QString ("file:///") + RESOURCES);
  engine.load (url);
  
  return app.exec();
}
