#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <clientnetwork.h>


int main (int argc, char* argv[]) {
  QGuiApplication app (argc, argv);
  

   qmlRegisterType<ClientNetWork>("com.neochat.network", 1, 0, "NeoChatNetoWork");


  QQmlApplicationEngine engine;
  QQmlContext *context = engine.rootContext();

//  qmlRegisterType<ClientNetWork>("com.network.chatclient",1,0,"ClientNetWork");
//  context->setContextProperty("clientNetWork",ClientNetWork::getInstance());


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
