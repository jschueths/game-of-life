//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author jschueths
/// @brief This is the basic Qt main file to begin the Qt app.
//////////////////////////////////////////////////////////////////////

#include <QApplication>
#include "Life_window.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  LifeWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
