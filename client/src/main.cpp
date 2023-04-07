#include <QApplication>
#include "MainWindow/MainWindow.hpp"

int main (int argc, char* argv[]) {
  QApplication a (argc, argv);
  MainWindow w;
  QObject::connect (&w, &MainWindow::Quit, &a, &QApplication::quit);
  w.show();
  return a.exec();
}
