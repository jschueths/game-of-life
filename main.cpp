// main.cpp

#include <QApplication>
#include "Life_window.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  LifeWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
