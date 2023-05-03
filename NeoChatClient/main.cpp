#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "modules/BaseCommun/basecommun.h"


int main (int argc, char* argv[]) {
  QGuiApplication app (argc, argv);
  
  
  
  
  QQmlApplicationEngine engine;
  QQmlContext* context = engine.rootContext();
  
  qmlRegisterType<BaseCommun>("BaseCommun",1,0,"BaseCommunObject");
  
  app.setOrganizationName("NeoChat");
  app.setOrganizationDomain("neochat.com");
  app.setApplicationName("Neochat chat");
  const QUrl url (u"qrc:/qml/Main.qml"_qs);
  QObject::connect (&engine, &QQmlApplicationEngine::objectCreationFailed,
  &app, []() { QCoreApplication::exit (-1); },
  Qt::QueuedConnection);
  engine.rootContext()->setContextProperty ("RES",
      QString ("file:///") + RESOURCES);
  engine.load (url);
  
  return app.exec();
}
